//
// Created by Eneko on 21/03/2025.
//
#include <catch2/catch_test_macros.hpp>

int theAnswer() { return 6 * 9; } // function to be tested

TEST_CASE("Life, the universe and everything", "[TestExample]") {
    REQUIRE(theAnswer() == 42);
}
