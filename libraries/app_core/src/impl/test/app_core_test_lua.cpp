#include "pch.h"

#include "app_core/app_core.h"

//#define SOL_ALL_SAFETIES_ON 1
//#define SOL_EXCEPTIONS_SAFE_PROPAGATION 1
//#define SOL_NO_EXCEPTIONS 1
//#define SOL_PRINT_ERRORS 1
#include <sol/sol.hpp>

static void s_my_lua_panic(sol::optional<std::string> maybe_msg) {
    std::cerr << "Lua is in a panic state and will now abort() the application" << std::endl;
    if (maybe_msg) {
        const auto &msg = maybe_msg.value();
        std::cerr << "\terror message: " << msg << std::endl;
    }
    // When this function exits, Lua will exhibit default behavior and abort()
}

void app_core_test_lua(void) {
    PRINT_FUNCTION_NAME();

    sol::state lua_state {
        #if SOL_NO_EXCEPTIONS
        sol::c_call<decltype(&s_my_lua_panic), s_my_lua_panic>
        #endif
    };
    lua_state.open_libraries(/*sol::lib::ffi, sol::lib::jit*/);

    {
        lua_state.new_usertype<GameObject>(
            "GameObject", sol::constructors<GameObject(int)>(),
            "get_id", &GameObject::get_id,
            "get_name", &GameObject::get_name,
            "set_name", &GameObject::set_name
        );
    }

    {
        lua_state["hello"] = [=](const std::shared_ptr<GameObject> &go) {
            printf("3-3, <LUA>: %s\n", go->get_name().c_str());
        };
        lua_state["yield"] = sol::yielding([=](double seconds) {
            return seconds;
        });
    }

    sol::object version = lua_state["_VERSION"];
    printf("1-1, <LUA>: %s\n", version.as<std::string>().c_str());

    try {
        lua_state.script(R"(print9('error\n'))");
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    auto result = lua_state.script("print('1-2, <LUA>: hello')");
    assert(result.valid());

    try {
        lua_state.script_file("assets/scripts/main.lua");

        {
            sol::function hi_func = lua_state["hi"];

            auto go = GameObject::create();
            go->set_name("John");

            hi_func(go);
            lua_state["hi2"](go);
            lua_state["hello"](go);
        }

        lua_state.script(R"(print('4, <LUA>: bye'))");
    } catch (const sol::error &e) {
        std::cout << e.what() << std::endl;
    }
    
    printf("5, <LUA>: bye bye!\n");
}