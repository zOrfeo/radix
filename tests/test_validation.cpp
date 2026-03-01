#include <catch2/catch_test_macros.hpp>
#include "validation/validation.h"
#include "constants.h"


TEST_CASE("Validate Binary Numbers", "[validation][binary]") {

    SECTION("Valid binary inputs") {
        CHECK(validateBinary("0") == ALL_OK);
        CHECK(validateBinary("1") == ALL_OK);
        CHECK(validateBinary("1010") == ALL_OK);
        CHECK(validateBinary("00001111") == ALL_OK);

        // 32-character valid binary string
        CHECK(validateBinary("10101010101010101010101010101010") == ALL_OK);
    }

    SECTION("Invalid binary inputs") {
        // invalid characters
        CHECK(validateBinary("2") == INVLD_NUM_ERR);
        CHECK(validateBinary("10201") == INVLD_NUM_ERR);
        CHECK(validateBinary("abc") == INVLD_NUM_ERR);

        // 32-character with invalid char
        CHECK(validateBinary("1010101010101010101010101010101G") == INVLD_NUM_ERR);
    }
}

TEST_CASE("Validate Octal Numbers", "[validation][octal]") {

    SECTION("Valid octal inputs") {
        CHECK(validateOctal("0") == ALL_OK);
        CHECK(validateOctal("7") == ALL_OK);
        CHECK(validateOctal("123") == ALL_OK);
        CHECK(validateOctal("76543210") == ALL_OK);

        // 32-character valid octal string
        CHECK(validateOctal("12345670123456701234567012345670") == ALL_OK);
    }

    SECTION("Invalid octal inputs") {
        // invalid characters
        CHECK(validateOctal("8") == INVLD_NUM_ERR);
        CHECK(validateOctal("128") == INVLD_NUM_ERR);
        CHECK(validateOctal("abc") == INVLD_NUM_ERR);

        // 32-character with invalid char
        CHECK(validateOctal("1234567012345670123456701234567A") == INVLD_NUM_ERR);
    }
}

TEST_CASE("Validate Decimal Numbers", "[validation][decimal]") {

    SECTION("Valid decimal inputs") {
        CHECK(validateDecimal("0") == ALL_OK);
        CHECK(validateDecimal("9") == ALL_OK);
        CHECK(validateDecimal("12345") == ALL_OK);
        CHECK(validateDecimal("00001234") == ALL_OK);

        // 32-character valid decimal string
        CHECK(validateDecimal("12345678901234567890123456789012") == ALL_OK);
    }

    SECTION("Invalid decimal inputs") {
        // invalid characters
        CHECK(validateDecimal("12A45") == INVLD_NUM_ERR);
        CHECK(validateDecimal("12.34") == INVLD_NUM_ERR);
        CHECK(validateDecimal("-123") == INVLD_NUM_ERR);

        // 32-character with invalid char
        CHECK(validateDecimal("1234567890123456789012345678901X") == INVLD_NUM_ERR);
    }
}

TEST_CASE("Validate Hexadecimal Numbers", "[validation][hex]") {

    SECTION("Valid hexadecimal inputs") {
        CHECK(validateHexadecimal("0") == ALL_OK);
        CHECK(validateHexadecimal("9") == ALL_OK);
        CHECK(validateHexadecimal("A") == ALL_OK);
        CHECK(validateHexadecimal("F") == ALL_OK);
        CHECK(validateHexadecimal("1A3F") == ALL_OK);

        // 32-character valid hexadecimal string
        CHECK(validateHexadecimal("ABCDEF0123456789ABCDEF0123456789") == ALL_OK);
    }

    SECTION("Invalid hexadecimal inputs") {
        // invalid characters
        CHECK(validateHexadecimal("G") == INVLD_NUM_ERR);
        CHECK(validateHexadecimal("1Z3") == INVLD_NUM_ERR);
        CHECK(validateHexadecimal("xyz") == INVLD_NUM_ERR);

        // 32-character with invalid char
        CHECK(validateHexadecimal("ABCDEF0123456789ABCDEF012345678G") == INVLD_NUM_ERR);
    }
}
