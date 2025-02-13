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

#if defined(__clang__)
    #define FUNCTION_NAME                                       __PRETTY_FUNCTION__

    #define PRAGMA(x)                                           _Pragma(#x)
    #define PRAGMA_WARNING_PUSH                                 PRAGMA(clang diagnostic push)
    #define PRAGMA_WARNING_POP                                  PRAGMA(clang diagnostic pop)
    #define PRAGMA_WARNING_IGNORE_CLANG(x)                      PRAGMA(clang diagnostic ignored x)
#else
    #define PRAGMA_WARNING_IGNORE_CLANG(x)
#endif

#if defined(__GNUC__)
    #define FUNCTION_NAME                                       __PRETTY_FUNCTION__

    #define PRAGMA(x)                                           _Pragma(#x)
    #define PRAGMA_WARNING_PUSH                                 PRAGMA(GCC diagnostic push)
    #define PRAGMA_WARNING_POP                                  PRAGMA(GCC diagnostic pop)
    #define PRAGMA_WARNING_IGNORE_GCC(x)                        PRAGMA(GCC diagnostic ignored x)
#else
    #define PRAGMA_WARNING_IGNORE_GCC(x)
#endif

#if defined(_MSC_VER)
    #define FUNCTION_NAME                                       __FUNCTION__

    #define PRAGMA(x)                                           __pragma(#x)
    #define PRAGMA_WARNING_PUSH                                 PRAGMA(warning(push))
    #define PRAGMA_WARNING_POP                                  PRAGMA(warning(pop))
    #define PRAGMA_WARNING_IGNORE_MSVC(x)                       PRAGMA(warning(disable : x))
#else
    #define PRAGMA_WARNING_IGNORE_MSVC(x)
#endif

#define PRINT_FUNCTION_NAME()                                   printf("\n%s\n", FUNCTION_NAME)
#define COUNTOF(arr)                                            (sizeof(arr) / sizeof(arr[0]))