#include <app_core.h>
#include <app_core_web.h>

#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>

extern "C" {
    JNIEXPORT void Java_com_wkslight_example_main_1activity_app_1init(void *args) {
        __android_log_write(ANDROID_LOG_INFO, "CPP", "hi from c++");

        //app_core();
    }
}

#else

int main(int argc, char *argv[]) {
    app_core();

    int ret = 0;
#ifdef TARGET_WEB
    ret = app_core_web_init();
#endif
    return ret;
}

#endif