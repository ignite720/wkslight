#pragma once

#ifdef BAR_STATIC_LIB
    #define BAR_TEMPLATE_EXTERN
    #define BAR_API
#else
    #ifdef BAR_BUILD_AS_DLL
        #define BAR_TEMPLATE_EXTERN

        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllexport)
        #else
            #define BAR_API                                     __attribute__((visibility("default")))
        #endif
    #else
        #define BAR_TEMPLATE_EXTERN                             extern
        
        #ifdef _WIN32
            #define BAR_API                                     __declspec(dllimport)
        #else
            #define BAR_API
        #endif
    #endif
#endif