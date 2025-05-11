#include "pch.h"

#include "app_core/app_core.h"

#include <magic_enum/magic_enum.hpp>

template <typename E>
static auto s_to_integer(magic_enum::Enum<E> value) {
    return static_cast<magic_enum::underlying_type_t<E>>(value);
}

void app_core_test_enum(void) {
    PRINT_FUNCTION_NAME();

    enum class Color : int {
        RED = -10,
        BLUE = 0,
        GREEN = 10
    };

    Color c1 = Color::RED;
    auto c1_name = magic_enum::enum_name(c1);
    std::cout << c1_name << std::endl;

    constexpr auto names = magic_enum::enum_names<Color>();
    std::cout << "Color names:";
    for (const auto &n : names) {
        std::cout << " " << n;
    }
    std::cout << std::endl;

    auto c2 = magic_enum::enum_cast<Color>("BLUE");
    if (c2.has_value()) {
        std::cout << "BLUE = " << s_to_integer(c2.value()) << std::endl;
    }

    c2 = magic_enum::enum_cast<Color>("blue", magic_enum::case_insensitive);
    if (c2.has_value()) {
        std::cout << "BLUE = " << s_to_integer(c2.value()) << std::endl;
    }

    auto c3 = magic_enum::enum_cast<Color>(10);
    if (c3.has_value()) {
        std::cout << "GREEN = " << magic_enum::enum_integer(c3.value()) << std::endl;
    }

    auto c4_integer = magic_enum::enum_integer(Color::RED);
    std::cout << "RED = " << c4_integer << std::endl;
}