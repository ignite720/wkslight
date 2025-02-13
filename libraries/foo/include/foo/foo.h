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

        template<
            typename Key,
            typename T,
            typename Hash = std::hash<Key>,
            typename KeyEqual = std::equal_to<Key>,
            typename Allocator = std::allocator<std::pair<const Key, T>>
        >
        using HashMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;
    }
}

using namespace rs;
using namespace rs::string;
using namespace rs::vec;

#include "foo/foo_api.h"

#if 0
FOO_TEMPLATE_EXTERN template
class FOO_API rs::string::String;
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
    void print(int n);
};