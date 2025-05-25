#include <catch2/catch.hpp>

TEST_CASE("Test case 1") {
    CHECK("1" != "x");
    CHECK_FALSE("1" == "x");

    REQUIRE(1 == 1);
    REQUIRE_FALSE(1 != 1);
}