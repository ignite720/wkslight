#pragma once

#include "foo/foo_api.h"
#include "foo/foo_types.h"

#if 0
FOO_TEMPLATE_EXTERN template class FOO_API rs::string::String;
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