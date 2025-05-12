#include "pch.h"

#include "app_core/app_core.h"

#include <wkstk/logging.hpp>

void app_core_test_logging(void) {
    PRINT_FUNCTION_NAME();

    logging::init();

    auto zero = "zero";
    auto one = fmt::format("{}", "one");
    auto two = fmt::format("{}", "two");
    auto three = 3;
    auto four = 4.12f;
    auto five = 5.123456789;

    LOG_TRACE("This is a trace message. {}", zero);
    LOG_DEBUG("This is a debug message. {}", one);
    LOG_INFO("This is a info message. {}", two);
    LOG_WARN("This is a warn[ing] message. Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", three);
    LOG_ERROR("This is a error message. {1:<30} {0}", four, "left aligned");
    LOG_CRITICAL("This is a critical message. Support for floats {:03.2f}", five);
}