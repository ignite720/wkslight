#pragma once

#include "app_core_api.h"

#ifdef __EMSCRIPTEN__

#define TARGET_WEB
//#define USE_ASSETS

extern "C" {
    APP_CORE_API int app_core_web_init();
}

#endif