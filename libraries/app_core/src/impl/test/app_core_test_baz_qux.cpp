#include "app_core/app_core.h"

#include <baz-qux/baz-qux.h>
#include <foo/foo_macros.h>

void app_core_test_baz_qux(void) {
    PRINT_FUNCTION_NAME();
    
    printf("baz_qux version: %d\n", baz_qux_version());
}