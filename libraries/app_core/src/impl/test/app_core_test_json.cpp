#include "pch.h"

#include "app_core/app_core.h"

#include <json/nlohmann/json.hpp>

void app_core_test_json(void) {
    PRINT_FUNCTION_NAME();

    JSON j;
    j["foo"] = 0.12345;
    j["bar"] = true;
    j["name"] = "John";
    j["foobar"] = nullptr;
    j["buzz"]["fizz"] = 30;
    j["tasks"] = { 100, 0, 150 };
    j["fruit"] = { { "name", "apple" }, { "price", 25.99 } };

    std::cout << "j = " << j.dump(4) << std::endl;
}