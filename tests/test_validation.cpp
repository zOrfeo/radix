#include <catch2/catch_test_macros.hpp>
#include "validation/validation.h"

TEST_CASE("Validate Binary Numbers", "[validation][binary]") {

    SECTION("Valid binary inputs") {
        CHECK(validateBinary("0") == true);
        CHECK(validateBinary("1") == true);
        CHECK(validateBinary("1010") == true);
        CHECK(validateBinary("00001111") == true);

        // 32-character valid binary string
        CHECK(validateBinary("10101010101010101010101010101010") == true);
    }

    SECTION("Invalid binary inputs") {
        // invalid characters
        CHECK(validateBinary("2") == false);
        CHECK(validateBinary("10201") == false);
        CHECK(validateBinary("abc") == false);

        // 32-character with invalid char
        CHECK(validateBinary("1010101010101010101010101010101G") == false);
    }
}

TEST_CASE("Validate Octal Numbers", "[validation][octal]") {

    SECTION("Valid octal inputs") {
        CHECK(validateOctal("0") == true);
        CHECK(validateOctal("7") == true);
        CHECK(validateOctal("123") == true);
        CHECK(validateOctal("76543210") == true);

        // 32-character valid octal string
        CHECK(validateOctal("12345670123456701234567012345670") == true);
    }

    SECTION("Invalid octal inputs") {
        // invalid characters
        CHECK(validateOctal("8") == false);
        CHECK(validateOctal("128") == false);
        CHECK(validateOctal("abc") == false);

        // 32-character with invalid char
        CHECK(validateOctal("1234567012345670123456701234567A") == false);
    }
}

TEST_CASE("Validate Decimal Numbers", "[validation][decimal]") {

    SECTION("Valid decimal inputs") {
        CHECK(validateDecimal("0") == true);
        CHECK(validateDecimal("9") == true);
        CHECK(validateDecimal("12345") == true);
        CHECK(validateDecimal("00001234") == true);

        // 32-character valid decimal string
        CHECK(validateDecimal("12345678901234567890123456789012") == true);
    }

    SECTION("Invalid decimal inputs") {
        // invalid characters
        CHECK(validateDecimal("12A45") == false);
        CHECK(validateDecimal("12.34") == false);
        CHECK(validateDecimal("-123") == false);

        // 32-character with invalid char
        CHECK(validateDecimal("1234567890123456789012345678901X") == false);
    }
}

TEST_CASE("Validate Hexadecimal Numbers", "[validation][hex]") {

    SECTION("Valid hexadecimal inputs") {
        CHECK(validateHexadecimal("0") == true);
        CHECK(validateHexadecimal("9") == true);
        CHECK(validateHexadecimal("A") == true);
        CHECK(validateHexadecimal("F") == true);
        CHECK(validateHexadecimal("a") == true);
        CHECK(validateHexadecimal("f") == true);
        CHECK(validateHexadecimal("1A3F") == true);
        CHECK(validateHexadecimal("1a3f") == true);
        CHECK(validateHexadecimal("0Bff") == true);

        // 32-character valid hexadecimal string
        CHECK(validateHexadecimal("ABCDEF0123456789ABCDEF0123456789") == true);
    }

    SECTION("Invalid hexadecimal inputs") {
        // invalid characters
        CHECK(validateHexadecimal("G") == false);
        CHECK(validateHexadecimal("1Z3") == false);
        CHECK(validateHexadecimal("xyz") == false);

        // 32-character with invalid char
        CHECK(validateHexadecimal("ABCDEF0123456789ABCDEF012345678G") == false);
    }
}
