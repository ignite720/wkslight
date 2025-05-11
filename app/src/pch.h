//#pragma once

#ifndef PCH_H
#define PCH_H

#if defined(__ANDROID__)

#include <jni.h>
#include <android/log.h>

#define LOG_TAG                                                 "WKSLIGHT"
#define LOGD(...)                                               __android_log_write(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...)                                               __android_log_write(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)                                               __android_log_write(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif

#endif