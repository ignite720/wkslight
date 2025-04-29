#pragma once

#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "foo/foo_api.h"

#if 0
FOO_TEMPLATE_EXTERN template class FOO_API std::string;
#endif

#ifdef __cplusplus
extern "C" {
#endif

FOO_API void foo_print(double n);
FOO_API void foo_printi(int n);
FOO_API void foo_printi64(int64_t n);

#ifdef __cplusplus
}
#endif

class FOO_API Foo {
public:
    Foo();
    ~Foo();

    void print(int n);

private:
    class Impl;
    Impl *m_impl = nullptr;
};