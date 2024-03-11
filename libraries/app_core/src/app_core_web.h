#pragma once

#include "app_core_api.h"

#ifdef __EMSCRIPTEN__
#define TARGET_WEB
//#define USE_ASSETS

C_API_BEGIN

APP_CORE_API int app_core_web_init();

C_API_END

#endif