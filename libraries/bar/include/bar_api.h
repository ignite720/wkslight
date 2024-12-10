#pragma once

#ifdef BAR_STATIC_LIB
    #define BAR_API
#else
    #ifdef BAR_BUILD_AS_DLL
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
#endif

#ifdef _WIN32
    #ifdef _MSC_VER
        /* msvc */
        #define TEMPLATE_EXTERN
    #else
        /* mingw */
        #define TEMPLATE_EXTERN                                 extern
    #endif
#else
    /* clang or gcc */
    #define TEMPLATE_EXTERN                                     extern
#endif