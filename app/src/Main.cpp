#include <foo.h>
#include <bar.h>

#include <linmath.h>

#include <tl/optional.hpp>

#include <iostream>
#include <memory>

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
bool load_texture(AppContext *ctx, const char *path, SDL_Texture **tex, int &w, int &h);

struct Player {
    static constexpr int MOVE_DELTA = 2;

    Player();
    ~Player();

    void init(AppContext *ctx);
    void update();
    void draw(AppContext *ctx);

    SDL_Texture *tex;
    SDL_Rect dst_rect;

    int move_state;
    vec2 v;
};

struct AppContext {
    ~AppContext();

    int init();

    SDL_Window *window;
    SDL_Renderer *renderer;

    Mix_Chunk *click_sound;
    std::unique_ptr<Player> player;
};

Player::Player()
    : tex(nullptr) {

}

Player::~Player() {2
    SDL_DestroyTexture(this->tex);
}

void Player::init(AppContext *ctx) {
    this->dst_rect.x = 100;
    this->dst_rect.y = 100;

    load_texture(ctx, "assets/player.png", &this->tex, this->dst_rect.w, this->dst_rect.h);
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
    SDL_RenderCopy(ctx->renderer, this->tex, nullptr, &this->dst_rect);
}

int AppContext::init() {
    const Uint32 flags = SDL_RENDERER_PRESENTVSYNC;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    this->window = SDL_CreateWindow("web", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 720, flags);
    this->renderer = SDL_CreateRenderer(this->window, -1, flags);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("failed to load 22.wav: %s\n", Mix_GetError());
        return 1;
    }
#if 0
    this->click_sound = Mix_LoadWAV("assets/click.wav");
    if (!this->click_sound) {
        printf("failed to load click.wav: %s\n", Mix_GetError());
        return 1;
    }
#endif

    this->player = std::make_unique<Player>();
    this->player->init(this);
    return 0;
}

AppContext::~AppContext() {
    this->player.reset();
    Mix_FreeChunk(this->click_sound);

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_CloseAudio();
    SDL_Quit();
}

bool load_texture(AppContext *ctx, const char *path, SDL_Texture **tex, int &w, int &h) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("img is null: %s\n", IMG_GetError());
        return false;
    }

    *tex = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    w = surface->w;
    h = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

void poll_events(AppContext *ctx) {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            Mix_PlayChannel(-1, ctx->click_sound, 0);
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

void g_main_loop(void *arg) {
    AppContext *ctx = (AppContext *) arg;

    poll_events(ctx);
    ctx->player->update();

    SDL_RenderClear(ctx->renderer);
    ctx->player->draw(ctx);

    SDL_RenderPresent(ctx->renderer);
}

int web_init() {
    g_ctx = std::make_unique<AppContext>();
    memset(g_ctx.get(), 0, sizeof(AppContext));
    if (g_ctx->init() != 0) {
        return 1;
    }

    constexpr int fps = -1;
    constexpr int simulate_infinite_loop = 1;
    emscripten_set_main_loop_arg(g_main_loop, g_ctx.get(), fps, simulate_infinite_loop);
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