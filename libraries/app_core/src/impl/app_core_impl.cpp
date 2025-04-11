#include "app_core/app_core.h"

static constexpr auto RESOLUTION_SCALE_FACTOR = int(2);
static constexpr auto WINDOW_WIDTH = int(1920 / RESOLUTION_SCALE_FACTOR);
static constexpr auto WINDOW_HEIGHT = int(1080 / RESOLUTION_SCALE_FACTOR);

static void s_test_gfx() {
    PRINT_FUNCTION_NAME();

    {
        auto app_core_gfx = AppCoreGfx::create(GfxApi::D3D12);
        app_core_gfx->test();
    }

    {
        auto app_core_gfx = AppCoreGfx::create(GfxApi::Vulkan);
        app_core_gfx->test();
    }
}

static int s_test_app_core() {
    PRINT_FUNCTION_NAME();

    auto app_core = AppCore::create();
    app_core->preload();
    
    int ret = 0;
    if ((ret = app_core->init(WINDOW_WIDTH, WINDOW_HEIGHT, false)) != 0) {
        return ret;
    }
    ret = app_core->run();
    return ret;
}

int app_core_startup(void) {
    PRINT_FUNCTION_NAME();

    app_core_test_logging();
    app_core_test_noise();

    app_core_test_rtm();
    app_core_test_xmath();

    app_core_test_bar();
    app_core_test_baz_qux();
    app_core_test_foo();

    app_core_test_json();
    app_core_test_enum();
    app_core_test_lua();

    s_test_gfx();
    return s_test_app_core();
}