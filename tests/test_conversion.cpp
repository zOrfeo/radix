#include <catch2/catch_test_macros.hpp>
#include "conversion/conversion.h"
#include "base.h"
#include <cstdint>

TEST_CASE("Convert from Binary", "[convert][binary]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("0", Base::BIN) == 0);
        CHECK(convertFromBase("1010", Base::BIN) == 10);
        CHECK(convertFromBase("11111111", Base::BIN) == 255);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("11111111111111111111111111111111111111111111111111111111111111111", Base::BIN) == UINT64_MAX);
    }
}

TEST_CASE("Convert from Octal", "[convert][octal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("10", Base::OCT) == 8);
        CHECK(convertFromBase("17", Base::OCT) == 15);
        CHECK(convertFromBase("01777777777777777777777", Base::OCT) == UINT64_MAX);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("01777777777777777777778", Base::OCT) == UINT64_MAX);
    }
}

TEST_CASE("Convert from Decimal", "[convert][decimal]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("123", Base::DEC) == 123);
        CHECK(convertFromBase("4294967295", Base::DEC) == UINT32_MAX);
        // UINT32 + 1
        CHECK(convertFromBase("4294967296", Base::DEC) == 4294967296);
        CHECK(convertFromBase("123", Base::DEC) == 123);
        CHECK(convertFromBase("000123", Base::DEC) == 123);
        CHECK(convertFromBase("123000", Base::DEC) == 123000);
        CHECK(convertFromBase(std::to_string(UINT64_MAX), Base::DEC) == UINT64_MAX);
    }

    SECTION("UINT64_MAX limited conversion") {
        CHECK(convertFromBase("18446744073709551616", Base::DEC) == UINT64_MAX);
        CHECK(convertFromBase("18446744073709551616", Base::DEC) == UINT64_MAX);
        CHECK(convertFromBase("99999999999999999999", Base::DEC) == UINT64_MAX);
    }
}

TEST_CASE("Convert from Hexadecimal", "[convert][hex]") {

    SECTION("Correct conversion") {
        CHECK(convertFromBase("A", Base::HEX) == 10);
        CHECK(convertFromBase("FF", Base::HEX) == 255);
        CHECK(convertFromBase("FFFFFFFFFFFFFFFF", Base::HEX) == UINT64_MAX);
        CHECK(convertFromBase("a", Base::HEX) == 10);
        CHECK(convertFromBase("ff", Base::HEX) == 255);
        CHECK(convertFromBase("ffffffffffffffff", Base::HEX) == UINT64_MAX);
    }

    SECTION("UINT32_MAX limited conversion") {
        CHECK(convertFromBase("0xFFFFFFFFFFFFFFFFA", Base::HEX) == UINT64_MAX);
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
