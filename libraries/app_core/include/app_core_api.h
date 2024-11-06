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

    #ifdef APP_CORE_STATIC
        #define APP_CORE_API                            extern
    #else
        #ifdef APP_CORE_BUILD_DLL
            #define APP_CORE_API                        __declspec(dllexport)
        #else
            #define APP_CORE_API                        __declspec(dllimport)
        #endif
    #endif
    
#else

    /* gcc or clang */
    #define TEMPLATE_EXTERN                             extern

    #define APP_CORE_API

#endif