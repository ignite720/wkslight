#pragma once

#if defined(__EMSCRIPTEN__)

#include <emscripten.h>
#include <emscripten/fetch.h>
#include <emscripten/html5.h>

#endif

#if 1
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#else
// todo: temporary test code
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

struct SDL_FPoint {
    float x;
    float y;
};

struct SDL_FRect {
    float x;
    float y;
    float w;
    float h;
};

inline SDL_bool SDL_HasIntersectionF(const SDL_FRect * A, const SDL_FRect * B) {
    auto a = SDL_Rect { int(A->x), int(A->y), int(A->w), int(A->h) };
    auto b = SDL_Rect { int(B->x), int(B->y), int(B->w), int(B->h) };
    return SDL_HasIntersection(&a, &b);
}

enum SDL_RendererFlip {
    SDL_FLIP_NONE = 0,
};

inline auto SDL_RenderCopyEx(
    SDL_Renderer *renderer,
    SDL_Texture *texture,
    const SDL_Rect *srcrect,
    const SDL_Rect *dstrect,
    const double angle,
    const SDL_Point *center,
    const SDL_RendererFlip flip
) -> int {
    return SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}
#endif

enum MOVE_STATE {
    MOVE_STATE_NONE = 0,
    MOVE_STATE_UP = 1 << 0,
    MOVE_STATE_DOWN = 1 << 1,
    MOVE_STATE_LEFT = 1 << 2,
    MOVE_STATE_RIGHT = 1 << 3,
};

struct WebObject {
    WebObject(AppCore *app_core) : m_app_core(app_core) {}
    virtual ~WebObject() = default;

protected:
    AppCore *m_app_core = nullptr;
};

namespace concepts {
    template<typename T>
    concept is_audio_music = std::is_same_v<T, Mix_Music>;

    template<typename T>
    concept is_audio_clip = std::is_same_v<T, Mix_Chunk>;
}

#define WEB_OBJECT_GET_RENDERER                                 reinterpret_cast<SDL_Renderer *>(m_app_core->renderer_as_void_p())