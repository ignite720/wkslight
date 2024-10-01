#include "app_core.h"

#include <bar.h>
#include <foo.h>

#include <json/nlohmann/json.hpp>

//#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

void app_core_init() {
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
        using JSON = nlohmann::json;

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

        lua.script("print('LUA: 3 => hello')");
        lua.do_file("assets/hello.lua");
#ifndef __EMSCRIPTEN__
        lua["hi"]("john");
#endif
    }
}