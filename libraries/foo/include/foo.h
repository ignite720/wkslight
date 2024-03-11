#pragma once

#include "foo_api.h"

#include <stdint.h>
#include <inttypes.h>

C_API_BEGIN

FOO_API void foo_print(double n);
FOO_API void foo_printi(int n);
FOO_API void foo_printi64(int64_t n);

C_API_END

class FOO_API Foo
{
public:
	void print(int n);
};