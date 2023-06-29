#include "foo.h"

#include <iostream>

void foo_print(double n)
{
	printf("foo: %f\n", n);
}

void foo_printi(int n)
{
	printf("foo: %d\n", n);
}

void foo_printi64(int64_t n)
{
	printf("foo: %" PRId64 "\n", n);
}

void Foo::print(int n)
{
	std::cout << "Foo: " << n << std::endl;
}