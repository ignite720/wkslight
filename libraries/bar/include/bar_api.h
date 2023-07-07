#pragma once

#ifdef _WIN32

    #ifdef _MSC_VER
        /* msvc */
        #define TEMPLATE_EXTERN
    #else
        /* mingw */
        #define TEMPLATE_EXTERN				extern
    #endif

    #ifdef BAR_BUILD_DLL
        #define BAR_API						__declspec(dllexport)
    #else
        #define BAR_API						__declspec(dllimport)
    #endif

#else

    /* gcc */
    #define TEMPLATE_EXTERN					extern

    #define BAR_API

#endif

#ifdef __cplusplus
    #define C_API_BEGIN						extern "C" {
#endif

#ifdef __cplusplus
    #define C_API_END						}
#endif