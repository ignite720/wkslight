#pragma once

#ifdef _WIN32

    #include <winapifamily.h>
    #ifdef _MSC_VER
        /* msvc */
        #define TEMPLATE_EXTERN
    #else
        /* mingw */
        #define TEMPLATE_EXTERN                         extern
    #endif

    #ifdef BAR_STATIC
        #define BAR_API                                 extern
    #else
        #ifdef BAR_BUILD_DLL
            #define BAR_API                             __declspec(dllexport)
        #else
            #define BAR_API                             __declspec(dllimport)
        #endif
    #endif
    
#else

    /* gcc or clang */
    #define TEMPLATE_EXTERN                             extern

    #define BAR_API

#endif