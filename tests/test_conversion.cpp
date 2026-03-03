#include <catch2/catch_test_macros.hpp>
#include "conversion/conversion.h"
#include "base.h"
#include "constants.h"
#include <cstdint>

TEST_CASE("Convert from Binary", "[convert][binary]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("0", Base::BIN) == 0);
        CHECK(convertFromBase("1010", Base::BIN) == 10);
        CHECK(convertFromBase("11111111", Base::BIN) == 255);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("111111111111111111111111111111111", Base::BIN) == UINT32_MAX);
    }
}

TEST_CASE("Convert from Octal", "[convert][octal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("10", Base::OCT) == 8);
        CHECK(convertFromBase("17", Base::OCT) == 15);
        CHECK(convertFromBase("037777777777", Base::OCT) == UINT32_MAX);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("40000000000", Base::OCT) == UINT32_MAX);
    }
}

TEST_CASE("Convert from Decimal", "[convert][decimal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("123", Base::DEC) == 123);
        CHECK(convertFromBase("4294967295", Base::DEC) == UINT32_MAX);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("4294967296", Base::DEC) == UINT32_MAX);
    }
}

TEST_CASE("Convert from Hexadecimal", "[convert][hex]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("A", Base::HEX) == 10);
        CHECK(convertFromBase("FF", Base::HEX) == 255);
        CHECK(convertFromBase("FFFFFFFF", Base::HEX) == UINT32_MAX);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("100000000", Base::HEX) == UINT32_MAX);
    }
}

TEST_CASE("Convert from Unknown (Decimal fallback)", "[convert][unknown]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("42", Base::UNKNOWN) == 42);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("4294967296", Base::UNKNOWN) == UINT32_MAX);
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
    CHECK(convertToBase(UINT32_MAX, Base::DEC) == "4294967295");
}

TEST_CASE("Convert to Hexadecimal", "[convert][hex]") {
    CHECK(convertToBase(10, Base::HEX) == "A");
    CHECK(convertToBase(255, Base::HEX) == "FF");
}

TEST_CASE("Convert to Unknown (Decimal fallback)", "[convert][unknown]") {
    CHECK(convertToBase(42, Base::UNKNOWN) == "42");
}

TEST_CASE("Convert String to UINT32", "[convert][decimal]") {
    SECTION ("Normal Conversion") {
        CHECK(stringToUInt32("123") == 123);
        CHECK(stringToUInt32("000123") == 123);
        CHECK(stringToUInt32("123000") == 123000);
        CHECK(stringToUInt32(std::to_string(UINT32_MAX)) == UINT32_MAX);
    }

    SECTION("UINT32_MAX Limited conversion") {
        CHECK(stringToUInt32("4294967296") == UINT32_MAX);
        CHECK(stringToUInt32("9999999999") == UINT32_MAX);
    }
}
