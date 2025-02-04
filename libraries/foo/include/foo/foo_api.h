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

#if defined(__clang__) || defined(__GNUC__)
    #define FUNCTION_NAME                                       __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNCTION_NAME                                       __FUNCTION__
#endif

#define PRINT_FUNCTION_NAME()                                   printf("%s\n", FUNCTION_NAME)
#define COUNTOF(arr)                                            (sizeof(arr) / sizeof(arr[0]))