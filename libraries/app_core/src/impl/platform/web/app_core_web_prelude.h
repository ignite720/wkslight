#pragma once

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

namespace concepts {
    template<typename T>
    concept is_music = std::is_same_v<T, Mix_Music>;

    template<typename T>
    concept is_clip = std::is_same_v<T, Mix_Chunk>;
}