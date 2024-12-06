#pragma once

#include "app_core.h"

#if (TARGET_PLATFORM_WEB == 1)

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <emscripten/html5.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

enum MOVE_STATE {
    MOVE_STATE_NONE = 0,
    MOVE_STATE_UP = 1 << 0,
    MOVE_STATE_DOWN = 1 << 1,
    MOVE_STATE_LEFT = 1 << 2,
    MOVE_STATE_RIGHT = 1 << 3,
};

struct Sound {
    ~Sound();

    bool load_from_file(const char *path);
    void play(int loops = 0) const;

private:
    Mix_Chunk *m_sound = nullptr;
};

struct Texture {
    ~Texture();

    bool load_from_file(SDL_Renderer *renderer, const char *path);

    SDL_Texture * get_raw_texture() const { return m_raw_texture; }

    int get_width() const { return m_width; }
    int get_height() const { return m_height; }

private:
    SDL_Texture *m_raw_texture = nullptr;
    int m_width = 0;
    int m_height = 0;
};

struct Player {
    static constexpr int MOVE_DELTA = 2;

    int get_move_state() const { return m_move_state; }
    void set_move_state(int value) { m_move_state = value; }

    void init(SDL_Renderer *renderer);
    void update();
    void render(SDL_Renderer *renderer);

private:
    std::unique_ptr<Texture> m_texture;
    SDL_Rect m_dst_rect = {};

    int m_move_state = MOVE_STATE_NONE;
    vec2 m_velocity;
};

namespace utils {
    String str_repeats(const String &s, size_t times);

    void fill_rect_with_color(SDL_Renderer *renderer, const SDL_Rect *rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void fill_rect_with_texture(SDL_Renderer *m_renderer, const SDL_Rect *rect, SDL_Texture *texture);

    void web_fetch(const String &url);
}

#endif