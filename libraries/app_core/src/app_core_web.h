#pragma once

#ifdef __EMSCRIPTEN__
#define TARGET_WEB
//#define USE_ASSETS

extern "C" {
    int app_core_web_init();
}
#endif