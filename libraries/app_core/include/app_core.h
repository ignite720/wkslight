#pragma once

#include "app_core_api.h"

#include <math.h>

extern "C" {
    APP_CORE_API void app_core_init();
}

struct APP_CORE_API vec2 {
    static float length(const vec2 &v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    static vec2 normalize(const vec2 &v) {
        const float len = vec2::length(v);

        vec2 ret = v;
        if (len != 0.0f) {
            ret.x /= len;
            ret.y /= len;
        }
        return ret;
    }

    float x = 0.0f;
    float y = 0.0f;
};