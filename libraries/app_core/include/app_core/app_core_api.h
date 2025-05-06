#pragma once

#ifdef APP_CORE_DLL
    #ifdef __APP_CORE_CONFIG_BUILD_DLL
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
#else
    #define APP_CORE_API
#endif