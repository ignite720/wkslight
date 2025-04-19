#pragma once

#if !TARGET_PLATFORM_ANDROID
    #if defined(_WIN32) || defined(__APPLE__)
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