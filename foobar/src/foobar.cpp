#include "foobar.h"

void foobar_default_init(foobar_t *foobar) {
    foobar->a = 1000;
    foobar->b = 2000.0f;
}

void foobar_print(const foobar_t *foobar) {
    printf("foobar_t { .a = %d, .b = %f }\n", foobar->a, foobar->b);
}