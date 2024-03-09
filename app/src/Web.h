#ifdef TARGET_WEB
#include <emscripten.h>
#include <emscripten/html5.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define MOVE_STATE_CASE(state) \
case SDLK_##state: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        this->player->move_state |= MOVE_STATE_##state; \
    } else if (evt.key.type == SDL_KEYUP) { \
        this->player->move_state ^= MOVE_STATE_##state; \
    } \
} break

enum MOVE_STATE {
    MOVE_STATE_NONE = 0,
    MOVE_STATE_UP = 1 << 0,
    MOVE_STATE_DOWN = 1 << 1,
    MOVE_STATE_LEFT = 1 << 2,
    MOVE_STATE_RIGHT = 1 << 3,
};

struct App;
struct Texture;

void fill_rect(SDL_Renderer *renderer, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
void fill_texture(SDL_Renderer *renderer, const SDL_Rect *rect, Texture *tex);

struct Sound {
    ~Sound();

    void load_from_file(const char *path);
    void play(int loops = 0) const;

    Mix_Chunk *sound = nullptr;
};

struct Texture {
    ~Texture();

    bool load_from_file(App *app, const char *path);

    SDL_Texture *texture = nullptr;
    int width = 0;
    int height = 0;
};

struct Player {
    static constexpr int MOVE_DELTA = 2;

    void init(App *app);
    void update();
    void draw(App *app);

    std::unique_ptr<Texture> tex;
    SDL_Rect dst_rect;

    int move_state = MOVE_STATE_NONE;
    vec2 v = { 0.0f, 0.0f };
};

struct App {
    ~App();

    int init(int width, int height, Uint32 flags = SDL_RENDERER_PRESENTVSYNC);
    void update();
    void draw();

    int window_width = 0;
    int window_height = 0;
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

void Sound::play(int loops) const {
    Mix_PlayChannel(-1, this->sound, loops);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
}

bool Texture::load_from_file(App *app, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(app->renderer, surface);
    this->width = surface->w;
    this->height = surface->h;
    printf("Image loaded successfully: %s\n", path);

    SDL_FreeSurface(surface);
    return true;
}

void Player::init(App *app) {
#ifdef USE_ASSETS
    this->tex = std::make_unique<Texture>();
    this->tex->load_from_file(app, "assets/player.png");
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

void Player::draw(App *app) {
    if (this->tex) {
        fill_texture(app->renderer, &this->dst_rect, this->tex.get());
    } else {
        fill_rect(app->renderer, &this->dst_rect, 0, 255, 255);
    }
}

App::~App() {
    this->player.reset();
    this->click_sound.reset();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    Mix_CloseAudio();
    SDL_Quit();
}

int App::init(int width, int height, Uint32 flags) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    this->window_width = width;
    this->window_height = height;

    this->window = SDL_CreateWindow("web", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    this->renderer = SDL_CreateRenderer(this->window, -1, flags);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize audio: %s\n", Mix_GetError());
        return 1;
    }
    
#ifdef USE_ASSETS
    this->click_sound = std::make_unique<Sound>();
    this->click_sound->load_from_file("assets/click.wav");
    if (!this->click_sound) {
        printf("Failed to load sound: %s\n", Mix_GetError());
        return 1;
    }
#endif

    this->player = std::make_unique<Player>();
    this->player->init(this);
    return 0;
}

void App::update() {
    SDL_Event evt = {0};
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (this->click_sound) {
                this->click_sound->play();
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

    this->player->update();
}

void App::draw() {
    SDL_RenderClear(this->renderer);

    {
        const SDL_Rect dst_rect{ 0, 0, this->window_width, this->window_height };
        fill_rect(this->renderer, &dst_rect, 25, 25, 25, 255);
    }

    this->player->draw(this);
    SDL_RenderPresent(this->renderer);
}

void fill_rect(SDL_Renderer *renderer, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, rect);
}

void fill_texture(SDL_Renderer *renderer, const SDL_Rect *rect, Texture *tex) {
    SDL_RenderCopy(renderer, tex->texture, nullptr, rect);
}
#endif