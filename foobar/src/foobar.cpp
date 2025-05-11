#include "foobar/foobar.h"

#include <stdio.h>

#include <typeinfo>

#include <spdlog/spdlog.h>

int foobar_version(void) {
    return FOOBAR_VERSION;
}

void foobar_default_init(foobar_t *foobar) {
    foobar->a = 1000;
    foobar->b = 2000.0f;
}

void foobar_print(const foobar_t *foobar) {
    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);
    
    SPDLOG_INFO("{} {{ .a = {}, .b = {} }}", typeid(*foobar).name(), foobar->a, foobar->b);
}