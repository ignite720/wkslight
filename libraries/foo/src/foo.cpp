#include "foo.h"

#include <iostream>

void foo_print(double n) {
	printf("foo_print() => %f\n", n);
}

void foo_printi(int n) {
	printf("foo_printi() => %d\n", n);
}

void foo_printi64(int64_t n) {
	printf("foo_printi64() => %" PRId64 "\n", n);
}

void Foo::print(int n) {
	std::cout << "Foo.print() => " << n << std::endl;
}