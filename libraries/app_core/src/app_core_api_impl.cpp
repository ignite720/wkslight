#include "pch.h"

#include "app_core/app_core.h"
#include "app_core/app_core_gfx.h"

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

static int s_test_app_core(int argc, char *argv[]) {
    PRINT_FUNCTION_NAME();

    {
        printf("argc=%d\n", argc);
        for (int i = 0; i < argc; ++i) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
    }

    #if !TARGET_PLATFORM_ANDROID
    auto app_core = AppCore::create();
    app_core->preload();
    
    int ret = 0;
    if ((ret = app_core->init("App", consts::WINDOW_WIDTH, consts::WINDOW_HEIGHT, false, false, argc >= 2 ? std::stoi(argv[1]) : 0)) != 0) {
        return ret;
    }
    
    ret = app_core->run();
    return ret;
    #else
    return 0;
    #endif
}

int app_core_startup(int argc, char *argv[]) {
    PRINT_FUNCTION_NAME();
    
    app_core_test_bar();
    app_core_test_baz_qux();
    app_core_test_enum();
    app_core_test_foo();

    app_core_test_json();
    app_core_test_logging();
    app_core_test_lua();

    app_core_test_noise();
    app_core_test_rtm();
    app_core_test_stb();
    app_core_test_xmath();
    
    s_test_gfx();
    return s_test_app_core(argc, argv);
}