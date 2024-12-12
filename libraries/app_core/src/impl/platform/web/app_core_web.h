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

#include "app_core_web_concepts.h"

#include "app_core_web_audio.h"
#include "app_core_web_texture.h"

#include "app_core_web_actor.h"
#include "app_core_web_ball.h"
#include "app_core_web_player.h"

#include "app_core_web_utils.h"

#endif