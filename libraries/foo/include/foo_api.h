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

    #ifdef FOO_STATIC
        #define FOO_API                                 extern
    #else
        #ifdef FOO_BUILD_DLL
            #define FOO_API                             __declspec(dllexport)
        #else
            #define FOO_API                             __declspec(dllimport)
        #endif
    #endif
    
#else

    /* gcc or clang */
    #define TEMPLATE_EXTERN                             extern

    #define FOO_API

#endif