#include "pch.h"

#include "app_core/app_core.h"

#include <bar/bar.h>

void app_core_test_bar(void) {
    PRINT_FUNCTION_NAME();

    Bar<int> bar;
    bar.print(100);

    Bar<float> bar2;
    bar2.print(101.0f);

#if 0
    Bar<double> bar3; // LNK2019
    bar3.print(201.0);
#endif
}