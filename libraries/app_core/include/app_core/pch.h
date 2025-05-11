//#pragma once

#include <foo/foo.h>

// emsdk
#if defined(__EMSCRIPTEN__)
    #include <emscripten.h>
    #include <emscripten/fetch.h>
    #include <emscripten/html5.h>
    #include <emscripten/websocket.h>
#endif


// sdl2
#if !TARGET_PLATFORM_ANDROID
    #if defined(_WIN32)/* || defined(__APPLE__)*/
        #include <SDL.h>
        #include <SDL_image.h>
        #include <SDL_mixer.h>
        #include <SDL_net.h>
        #include <SDL_ttf.h>
    #else
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
        #include <SDL2/SDL_mixer.h>
        #include <SDL2/SDL_net.h>
        #include <SDL2/SDL_ttf.h>
    #endif
#endif


// mathx
#include <mathx/mathx_rtm.h>
using namespace rtm;

#if !defined(__APPLE__)
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_IGNORE_CLANG("-Wattributes")
PRAGMA_WARNING_IGNORE_GCC("-Wattributes")
PRAGMA_WARNING_IGNORE_MSVC(4616)
#include <mathx/mathx_xmath.h>
PRAGMA_WARNING_POP

using namespace XMath;
#endif


#include "app_core/app_core_fwd.h"
#include "app_core/consts.h"