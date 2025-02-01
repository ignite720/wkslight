#include "foobar/foobar.h"

#include <stdio.h>

#include <typeinfo>

void foobar_default_init(foobar_t *foobar) {
    foobar->a = 1000;
    foobar->b = 2000.0f;
}

void foobar_print(const foobar_t *foobar) {
    printf("%s { .a = %d, .b = %f, }\n", typeid(*foobar).name(), foobar->a, foobar->b);
}