#include "app_core/app_core.h"

#include <foo/foo.h>
#include <foo/foo_macros.h>

void app_core_test_foo(void) {
    PRINT_FUNCTION_NAME();

    foo_print(10.0);
    foo_printi(20);
    foo_printi64(30000123456789);

    Foo foo;
    foo.print(400);
}