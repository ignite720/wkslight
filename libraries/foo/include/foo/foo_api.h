#pragma once

#ifdef FOO_DLL
    #ifdef __FOO_CONFIG_BUILD_DLL
        #ifdef _WIN32
            #define FOO_API                                     __declspec(dllexport)
        #else
            #define FOO_API                                     __attribute__((visibility("default")))
        #endif
    #else
        #ifdef _WIN32
            #define FOO_API                                     __declspec(dllimport)
        #else
            #define FOO_API
        #endif
    #endif
#else
    #define FOO_API
#endif