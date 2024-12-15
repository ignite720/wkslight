#include "app_core.h"

#include <bar.h>

#include <json/nlohmann/json.hpp>
using JSON = nlohmann::json;

//#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

int app_core_startup() {
    PRINT_FUNCTION_NAME();

    {
        Bar<int> bar;
        bar.print(100);

        Bar<float> bar2;
        bar2.print(101.0f);

#if 0
        Bar<double> bar3; // LNK2019
        bar3.print(201.0);
#endif
    }

    {
        foo_print(10.0);
        foo_printi(20);
        foo_printi64(30000123456789);

        Foo foo;
        foo.print(400);
    }

    {
        JSON j;
        j["foo"] = 0.12345;
        j["bar"] = true;
        j["name"] = "John";
        j["baz"] = nullptr;
        j["buzz"]["fizz"] = 30;
        j["tasks"] = { 100, 0, 150 };
        j["fruit"] = { {"name", "apple"}, {"price", 25.99} };
        std::cout << "j = " << j.dump(4) << std::endl;
    }

    {
        sol::state lua;
        lua.open_libraries(/*sol::lib::base*/);

        auto result = lua.script("print('LUA: 3 => hello')");
        auto result2 = lua.do_file("assets/scripts/hello.lua");
        if (result2.valid()) {
            sol::function hi_func = lua["hi"];
            hi_func("john");
        }
    }

    auto app_core_gfx = AppCoreGfx::create(GfxApi::Vulkan);
    app_core_gfx->test();
    
    auto app_core = AppCore::create();
    int ret = 0;
    if ((ret = app_core->init(1920 / 4, 1080 / 4, false)) != 0) {
        return ret;
    }
    ret = app_core->run();
    return ret;
}

std::unique_ptr<AppCore> AppCore::create() {
    #if TARGET_PLATFORM_ANDROID
    return AppCore::create_android();
    #elif TARGET_PLATFORM_PC
    return AppCore::create_pc();
    #elif TARGET_PLATFORM_UWP
    return AppCore::create_uwp();
    #elif TARGET_PLATFORM_WEB
    return AppCore::create_web();
    #else
    return nullptr;
    #endif
}

std::unique_ptr<AppCoreGfx> AppCoreGfx::create(GfxApi api) {
    switch (api) {
        case GfxApi::D3D12: {
            return AppCoreGfx::create_d3d12();
        } break;
        case GfxApi::Vulkan: {
            return AppCoreGfx::create_vulkan();
        } break;
        default: {
            assert(false);
            return nullptr;
        } break;
    }
}