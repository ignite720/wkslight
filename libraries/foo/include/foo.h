#pragma once

#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

using String = std::string;

template<typename T>
using Vec = std::vector<T>;

#include "foo_api.h"

extern "C" {
    FOO_API void foo_print(double n);
    FOO_API void foo_printi(int n);
    FOO_API void foo_printi64(int64_t n);
}

struct FOO_API Foo {
    void print(int n);
};