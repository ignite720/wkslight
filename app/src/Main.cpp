#include <foo.h>
#include <bar.h>

#include <linmath.h>

#include <tl/optional.hpp>

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define MOVE_STATE_CASE(state) \
case SDLK_##state: { \
    if (evt.key.type == SDL_KEYDOWN) { \
        ctx->player.move_state |= MOVE_STATE_##state; \
    } else if (evt.key.type == SDL_KEYUP) { \
        ctx->player.move_state ^= MOVE_STATE_##state; \
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
bool load_texture(AppContext *ctx, const char *path, SDL_Texture *tex, int &w, int &h);

struct Player {
    static constexpr int MOVE_DELTA = 2;

    void init(AppContext *ctx);
    void update();
    void draw(AppContext *ctx);

    SDL_Texture *tex;
    SDL_Rect dst_rect;

    int move_state;
    vec2 v;
};

struct AppContext {
    SDL_Window *window;
    SDL_Renderer *renderer;

    Mix_Chunk *click_sound;
    Player player;
};

void Player::init(AppContext *ctx) {
    load_texture(ctx, "assets/player.png", this->tex, this->dst_rect.w, this->dst_rect.h);
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

bool load_texture(AppContext *ctx, const char *path, SDL_Texture *tex, int &w, int &h) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        return false;
    }

    tex = SDL_CreateTextureFromSurface(ctx->renderer, surface);
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
        }
    }
}

void main_loop(void *arg) {
    AppContext *ctx = (AppContext *) ctx;
    if (!ctx) {
        return;
    }

    poll_events(ctx);
    ctx->player.update();

    SDL_RenderClear(ctx->renderer);
    ctx->player.draw(ctx);

    SDL_RenderPresent(ctx->renderer);
}

int web_init() {
    AppContext ctx = {0};
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return 1;
    }

    SDL_CreateWindowAndRenderer(1280, 720, 0, &ctx.window, &ctx.renderer);
    SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return 1;
    }

    ctx.player.init(&ctx);

    const int fps = -1;
    const int simulate_infinite_loop = 1;
    emscripten_set_main_loop_arg(main_loop, &ctx, fps, simulate_infinite_loop);

    SDL_DestroyWindow(ctx.window);
    Mix_CloseAudio();
    SDL_Quit();
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
#ifdef __EMSCRIPTEN__
    ret = web_init();
#endif
    return ret;
}