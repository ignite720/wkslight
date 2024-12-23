#pragma once

#ifdef APP_CORE_STATIC_LIB
    #define APP_CORE_API
#else
    #ifdef APP_CORE_BUILD_AS_DLL
        #ifdef _WIN32
            #define APP_CORE_API                                __declspec(dllexport)
        #else
            #define APP_CORE_API                                __attribute__((visibility("default")))
        #endif
    #else
        #ifdef _WIN32
            #define APP_CORE_API                                __declspec(dllimport)
        #else
            #define APP_CORE_API
        #endif
    #endif
#endif