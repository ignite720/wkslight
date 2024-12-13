#pragma once

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

using String = std::string;

#include "foo_api.h"

extern "C" {
    FOO_API void foo_print(double n);
    FOO_API void foo_printi(int n);
    FOO_API void foo_printi64(int64_t n);
}

struct FOO_API Foo {
    void print(int n);
};