#include "app_core.h"

#include <foobar.h>

#include <bar.h>
#include <foo.h>

//#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include <optional/tl/optional.hpp>

#include <thread>

#include <chrono>
using namespace std::chrono_literals;

void app_core_init() {
    {
        FooBar fb;
        fb.print();
    }

    {
        foo_print(10.0);
        foo_printi(20);
        foo_printi64(30000123456789);

        Foo foo;
        foo.print(40);
    }

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
        vec3 r;

        vec3 i = { 1, 0, 0 };
        vec3 j = { 0, 1, 0 };
        vec3 k = { 0, 0, 1 };
        vec3_mul_cross(r, i, j);

        vec3_add(r, i, j);
        vec3_add(r, r, k);
    }

    {
        tl::optional<int> opt1;
        opt1 = 500;
        if (opt1) {
            std::cout << "opt1: " << opt1.value() << std::endl;
        }
    }

    {
        sol::state lua;
        lua.open_libraries(/*sol::lib::base*/);

        lua.script("print('LUA: 3 => hello')");

        lua.do_file("assets/hello.lua");
#ifndef __EMSCRIPTEN__
        lua["hello"]("john");
#endif
    }
}