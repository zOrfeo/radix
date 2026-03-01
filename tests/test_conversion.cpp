#include <catch2/catch_test_macros.hpp>
#include "conversion/conversion.h"
#include "base.h"
#include "constants.h"
#include <climits>

TEST_CASE("Convert from Binary", "[convert][binary]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("0", Base::BIN) == 0);
        CHECK(convertFromBase("1010", Base::BIN) == 10);
        CHECK(convertFromBase("11111111", Base::BIN) == 255);
    }

    SECTION("INT_MAX limited conversion") {
        CHECK(convertFromBase("11111111111111111111111111111111", Base::BIN) == INT_MAX);
    }
}

TEST_CASE("Convert from Octal", "[convert][octal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("10", Base::OCT) == 8);
        CHECK(convertFromBase("17", Base::OCT) == 15);
    }

    SECTION("INT_MAX limited conversion") {
        CHECK(convertFromBase("37777777777", Base::OCT) == INT_MAX);
    }
}

TEST_CASE("Convert from Decimal", "[convert][decimal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("123", Base::DEC) == 123);
        CHECK(convertFromBase("2147483647", Base::DEC) == INT_MAX);
    }

    SECTION("INT_MAX limited conversion") {
        CHECK(convertFromBase("2147483648", Base::DEC) == INT_MAX);
    }
}

TEST_CASE("Convert from Hexadecimal", "[convert][hex]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("A", Base::HEX) == 10);
        CHECK(convertFromBase("FF", Base::HEX) == 255);
        CHECK(convertFromBase("7FFFFFFF", Base::HEX) == INT_MAX);
    }

    SECTION("INT_MAX limited conversion") {
        CHECK(convertFromBase("FFFFFFFF", Base::HEX) == INT_MAX);
    }
}

TEST_CASE("Convert from Unknown (Decimal fallback)", "[convert][unknown]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("42", Base::UNKNOWN) == 42);
    }

    SECTION("INT_MAX limited conversion") {
        CHECK(convertFromBase("2147483648", Base::UNKNOWN) == INT_MAX);
    }
}

TEST_CASE("Convert to Binary", "[convert][binary]") {
    CHECK(convertToBase(0, Base::BIN) == "0");
    CHECK(convertToBase(10, Base::BIN) == "1010");
    CHECK(convertToBase(255, Base::BIN) == "11111111");
}

TEST_CASE("Convert to Octal", "[convert][octal]") {
    CHECK(convertToBase(8, Base::OCT) == "10");
    CHECK(convertToBase(15, Base::OCT) == "17");
}

TEST_CASE("Convert to Decimal", "[convert][decimal]") {
    CHECK(convertToBase(123, Base::DEC) == "123");
    CHECK(convertToBase(INT_MAX, Base::DEC) == "2147483647");
}

TEST_CASE("Convert to Hexadecimal", "[convert][hex]") {
    CHECK(convertToBase(10, Base::HEX) == "A");
    CHECK(convertToBase(255, Base::HEX) == "FF");
}

TEST_CASE("Convert to Unknown (Decimal fallback)", "[convert][unknown]") {
    CHECK(convertToBase(42, Base::UNKNOWN) == "42");
}
