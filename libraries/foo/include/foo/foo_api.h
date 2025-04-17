#pragma once

#ifdef FOO_DLL
    #ifdef __FOO_CONFIG_BUILD_DLL
        #ifdef _WIN32
            #define FOO_API                                     __declspec(dllexport)
        #else
            #define FOO_API                                     __attribute__((visibility("default")))
        #endif

        #define FOO_TEMPLATE_EXTERN
    #else
        #ifdef _WIN32
            #define FOO_API                                     __declspec(dllimport)
        #else
            #define FOO_API
        #endif

        #define FOO_TEMPLATE_EXTERN                             extern
    #endif
#else
    #define FOO_API
    #define FOO_TEMPLATE_EXTERN
#endif