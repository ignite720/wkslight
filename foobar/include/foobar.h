#pragma once

#include <stdio.h>

typedef struct tag_foobar_t {
    int a;
    float b;
} foobar_t;

void foobar_default_init(foobar_t *foobar);
void foobar_print(const foobar_t *foobar);