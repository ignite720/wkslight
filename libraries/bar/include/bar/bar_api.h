#pragma once

#ifdef BAR_DLL
    #ifdef __BAR_CONFIG_BUILD_DLL
        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllexport)
        #else
            #define BAR_API                                     __attribute__((visibility("default")))
        #endif

        #define BAR_TEMPLATE_EXTERN
    #else
        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllimport)
        #else
            #define BAR_API
        #endif

        #define BAR_TEMPLATE_EXTERN                             extern
    #endif
#else
    #define BAR_API
    #define BAR_TEMPLATE_EXTERN
#endif