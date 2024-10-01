#include <app_core.h>
#include <app_core_web.h>

#ifdef __ANDROID__

#include <jni.h>
#include <android/log.h>

#define LOG_TAG "WKSLIGHT"
#define LOGD(...) __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_write(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" {
    JNIEXPORT void Java_com_wkslight_example_main_1activity_app_1init(void *args) {
        LOGI("2 => hello");

        app_core_init();
    }
}

#else

int main(int argc, char *argv[]) {
    app_core_init();

    int ret = 0;
#ifdef TARGET_WEB
    ret = app_core_web_init();
#endif
    return ret;
}

#endif