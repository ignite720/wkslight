#include "pch.h"

#include <foobar/foobar.h>

#include <app_core/pch.h>
#include <app_core/app_core.h>

static void s_print_env(const char *name) {
    PRINT_FUNCTION_NAME();
    
    auto value = getenv(name);
    printf("%s=%s\n", name, value);
}

static void s_test_foobar() {
    PRINT_FUNCTION_NAME();

    {
        printf("foobar version: %d\n", foobar_version());

        foobar_t foobar;
        foobar_default_init(&foobar);

        foobar_print(&foobar);
    }
}

static int s_main(int argc, char *argv[]) {
    PRINT_FUNCTION_NAME();

    {
        s_print_env("FOO");
        s_print_env("BAR");
    }

    s_test_foobar();
    return app_core_startup(argc, argv);
}

#if defined(__ANDROID__)

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint Java_com_wkslight_example_main_1activity_app_1init(JNIEnv *env, jclass clazz) {
    LOGI("0-2, <JNI>: world");

    const int argc = 1;
    constexpr const char *const argv[] = { "/proc/self/exe" };
    return s_main(argc, const_cast<char **>(argv));
}

#ifdef __cplusplus
}
#endif

#else

int main(int argc, char *argv[]) {
    return s_main(argc, argv);
}

#endif