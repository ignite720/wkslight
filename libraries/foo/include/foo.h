#pragma once

#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace rs {
    namespace string {
        using String = std::string;
    }

    namespace vec {
        template<typename T>
        using Vec = std::vector<T>;
    }

    namespace collections {
        template<typename K, typename V>
        using BTreeMap = std::map<K, V>;

        template<typename K, typename V>
        using HashMap = std::unordered_map<K, V>;
    }
}

using namespace rs;
using namespace rs::string;
using namespace rs::vec;

#include "foo_api.h"

extern "C" {
    FOO_API void foo_print(double n);
    FOO_API void foo_printi(int n);
    FOO_API void foo_printi64(int64_t n);
}

struct FOO_API Foo {
    void print(int n);
};