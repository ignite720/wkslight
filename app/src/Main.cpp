#include <foo.h>
#include <bar.h>

#include <linmath.h>

#include <tl/optional.hpp>

#include <iostream>
#include <memory>

//#define USE_ASSETS

static constexpr int WIN_WIDTH = 1280/2;
static constexpr int WIN_HEIGHT = 720/2;

#ifdef _WIN32
#if (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
// pc
#else
// uwp
#endif
#endif

#ifdef __EMSCRIPTEN__
#define TARGET_WEB
#endif

#ifdef TARGET_WEB
#include <stdio.h>

#include <emscripten.h>
#include <emscripten/html5.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define MOVE_STATE_CASE(state) \
case SDLK_##state: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        ctx->player->move_state |= MOVE_STATE_##state; \
    } else if (evt.key.type == SDL_KEYUP) { \
        ctx->player->move_state ^= MOVE_STATE_##state; \
    } \
} break

enum MOVE_STATE {
    MOVE_STATE_NONE = 0,
    MOVE_STATE_UP = 1 << 0,
    MOVE_STATE_DOWN = 1 << 1,
    MOVE_STATE_LEFT = 1 << 2,
    MOVE_STATE_RIGHT = 1 << 3,
};

struct AppContext;
void fill_rect(AppContext *ctx, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

struct Sound {
    ~Sound();

    void load_from_file(const char *path);
    void play() const;

    Mix_Chunk *sound = nullptr;
};

struct Texture {
    ~Texture();

    bool load_from_file(AppContext *ctx, const char *path);

    SDL_Texture *texture = nullptr;
    int width = 0;
    int height = 0;
};

struct Player {
    static constexpr int MOVE_DELTA = 2;

    void init(AppContext *ctx);
    void update();
    void draw(AppContext *ctx);

    std::unique_ptr<Texture> tex;
    SDL_Rect dst_rect;

    int move_state = MOVE_STATE_NONE;
    vec2 v = { 0.0f, 0.0f };
};

struct AppContext {
    ~AppContext();

    int init();

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    std::unique_ptr<Sound> click_sound;
    std::unique_ptr<Player> player;
};

Sound::~Sound() {
    Mix_FreeChunk(this->sound);
}

void Sound::load_from_file(const char *path) {
    this->sound = Mix_LoadWAV(path);
}

void Sound::play() const {
    Mix_PlayChannel(-1, this->sound, 0);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
}

bool Texture::load_from_file(AppContext *ctx, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("failed to load image: %s\n", IMG_GetError());
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    this->width = surface->w;
    this->height = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

void Player::init(AppContext *ctx) {
#ifdef USE_ASSETS
    this->tex = std::make_unique<Texture>();
    this->tex->load_from_file(ctx, "assets/player.png");
#endif

    this->dst_rect.x = 0;
    this->dst_rect.y = 0;

    if (this->tex) {
        this->dst_rect.w = this->tex->width;
        this->dst_rect.h = this->tex->height;
    } else {
        this->dst_rect.w = this->dst_rect.h = 32;
    }
}

void Player::update() {
    this->v[0] = this->v[1] = 0.0;
    if (this->move_state & MOVE_STATE_UP) {
        this->v[1] = -MOVE_DELTA;
    }
    if (this->move_state & MOVE_STATE_DOWN) {
        this->v[1] = +MOVE_DELTA;
    }
    if (this->move_state & MOVE_STATE_LEFT) {
        this->v[0] = -MOVE_DELTA;
    }
    if (this->move_state & MOVE_STATE_RIGHT) {
        this->v[0] = +MOVE_DELTA;
    }

    if (this->v[0] != 0.0f && this->v[1] != 0.0f) {
        vec2_norm(this->v, this->v);
    }

    this->dst_rect.x += this->v[0];
    this->dst_rect.y += this->v[1];
}

void Player::draw(AppContext *ctx) {
    if (this->tex) {
        SDL_RenderCopy(ctx->renderer, this->tex->texture, nullptr, &this->dst_rect);
    } else {
        fill_rect(ctx, &this->dst_rect, 0, 255, 255);
    }
}

int AppContext::init() {
    const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    this->window = SDL_CreateWindow("web", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, flags);
    this->renderer = SDL_CreateRenderer(this->window, -1, flags);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("failed to load 22.wav: %s\n", Mix_GetError());
        return 1;
    }
#ifdef USE_ASSETS
    this->click_sound = std::make_unique<Sound>();
    this->click_sound->load_from_file("assets/click.wav");
    if (!this->click_sound) {
        printf("failed to load sound: %s\n", Mix_GetError());
        return 1;
    }
#endif

    this->player = std::make_unique<Player>();
    this->player->init(this);
    return 0;
}

AppContext::~AppContext() {
    this->player.reset();
    this->click_sound.reset();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_CloseAudio();
    SDL_Quit();
}

void fill_rect(AppContext *ctx, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);
    SDL_RenderFillRect(ctx->renderer, rect);
}

static void poll_events(AppContext *ctx) {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (ctx->click_sound) {
                ctx->click_sound->play();
            }
        }

        switch (evt.key.keysym.sym) {
            MOVE_STATE_CASE(UP);
            MOVE_STATE_CASE(DOWN);
            MOVE_STATE_CASE(LEFT);
            MOVE_STATE_CASE(RIGHT);
            default: break;
        }
    }
}

std::unique_ptr<AppContext> g_ctx;

static void main_loop(void *arg) {
    AppContext *ctx = (AppContext *) arg;

    poll_events(ctx);
    ctx->player->update();

    SDL_RenderClear(ctx->renderer);
    const SDL_Rect dst_rect{ 0, 0, WIN_WIDTH, WIN_HEIGHT };
    fill_rect(ctx, &dst_rect, 25, 25, 25);

    ctx->player->draw(ctx);

    SDL_RenderPresent(ctx->renderer);
}

static int web_init() {
    g_ctx = std::make_unique<AppContext>();
    if (g_ctx->init() != 0) {
        return 1;
    }

    constexpr int fps = -1;
    constexpr int simulate_infinite_loop = 1;
    emscripten_set_main_loop_arg(main_loop, g_ctx.get(), fps, simulate_infinite_loop);
    return 0;
}
#endif

int main(int argc, char *argv[]) {
    {
        foo_print(10.0);
        foo_printi(20);
        foo_printi64(30000123456789);

        Foo foo;
        foo.print(40);
    }

    {
        Bar<int> bar;
        bar.print(100);

        Bar<float> bar2;
        bar2.print(101.0f);

#if 0
        Bar<double> bar3; // LNK2019
        bar3.print(201.0);
#endif
    }

    {
        vec3 r;

        vec3 i = { 1, 0, 0 };
        vec3 j = { 0, 1, 0 };
        vec3 k = { 0, 0, 1 };
        vec3_mul_cross(r, i, j);

        vec3_add(r, i, j);
        vec3_add(r, r, k);
    }

    {
        tl::optional<int> opt1;
        opt1 = 500;
        if (opt1) {
            std::cout << "opt1: " << opt1.value() << std::endl;
        }
    }

    int ret = 0;
#ifdef TARGET_WEB
    ret = web_init();
#endif
    return ret;
}