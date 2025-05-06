#pragma once

#ifdef BAR_DLL
    #ifdef __BAR_CONFIG_BUILD_DLL
        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllexport)
        #else
            #define BAR_API                                     __attribute__((visibility("default")))
        #endif
    #else
        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllimport)
        #else
            #define BAR_API
        #endif
    #endif
#else
    #define BAR_API
#endif