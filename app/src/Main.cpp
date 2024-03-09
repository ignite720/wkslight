#include <bar.h>
#include <foo.h>

#include <tl/optional.hpp>
#include <linmath.h>

#include <iostream>
#include <memory>

#ifdef __EMSCRIPTEN__
#define TARGET_WEB

#include "Web.h"

std::unique_ptr<App> g_app;

static void main_loop(void *arg) {
    App *app = (App *) arg;

    app->update();
    app->draw();
}

static int web_init() {
    g_app = std::make_unique<App>();
    if (g_app->init(1920 / 4, 1080 / 4) != 0) {
        return 1;
    }

    constexpr int fps = -1;
    constexpr int simulate_infinite_loop = 1;
    emscripten_set_main_loop_arg(main_loop, g_app.get(), fps, simulate_infinite_loop);
    return 0;
}
#endif

int main(int argc, char *argv[]) {
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

    int ret = 0;
#ifdef TARGET_WEB
    ret = web_init();
#endif
    return ret;
}