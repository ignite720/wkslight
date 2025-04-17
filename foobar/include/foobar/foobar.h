#pragma once

#define FOOBAR_VERSION 100

typedef struct tag_foobar_t {
    int a;
    float b;
} foobar_t;

#ifdef __cplusplus
extern "C" {
#endif

int foobar_version(void);

void foobar_default_init(foobar_t *foobar);
void foobar_print(const foobar_t *foobar);

#ifdef __cplusplus
}
#endif