#include <catch2/catch_test_macros.hpp>
#include "parsing/parsing.h"
#include "base.h"

TEST_CASE("Parse Binary Base Options", "[parse][option][binary]") {
    CHECK(parseBaseOption("b") == Base::BIN);
    CHECK(parseBaseOption("bin") == Base::BIN);
    CHECK(parseBaseOption("2") == Base::BIN);
}

TEST_CASE("Parse Octal Base Options", "[parse][option][octal]") {
    CHECK(parseBaseOption("o") == Base::OCT);
    CHECK(parseBaseOption("oct") == Base::OCT);
    CHECK(parseBaseOption("8") == Base::OCT);
}

TEST_CASE("Parse Decimal Base Options", "[parse][option][decimal]") {
    CHECK(parseBaseOption("d") == Base::DEC);
    CHECK(parseBaseOption("dec") == Base::DEC);
    CHECK(parseBaseOption("10") == Base::DEC);
}

TEST_CASE("Parse Hexadecimal Base Options", "[parse][option][hex]") {
    CHECK(parseBaseOption("h") == Base::HEX);
    CHECK(parseBaseOption("hex") == Base::HEX);
    CHECK(parseBaseOption("16") == Base::HEX);
}

TEST_CASE("Parse Invalid Base Options", "[parse][option][invalid]") {

    SECTION("Invalid Case") {
        CHECK(parseBaseOption("B") == Base::UNKNOWN);
        CHECK(parseBaseOption("BIN") == Base::UNKNOWN);
        CHECK(parseBaseOption("O") == Base::UNKNOWN);
        CHECK(parseBaseOption("OCT") == Base::UNKNOWN);
        CHECK(parseBaseOption("D") == Base::UNKNOWN);
        CHECK(parseBaseOption("DEC") == Base::UNKNOWN);
        CHECK(parseBaseOption("H") == Base::UNKNOWN);
        CHECK(parseBaseOption("HEX") == Base::UNKNOWN);
    }

    SECTION("Invalid Numeric") {
        CHECK(parseBaseOption("6") == Base::UNKNOWN);
        CHECK(parseBaseOption("15") == Base::UNKNOWN);
        CHECK(parseBaseOption("37") == Base::UNKNOWN);
        CHECK(parseBaseOption("3") == Base::UNKNOWN);
    }

    SECTION("Whitespace") {
        CHECK(parseBaseOption(" b") == Base::UNKNOWN);
        CHECK(parseBaseOption(" bin") == Base::UNKNOWN);
        CHECK(parseBaseOption(" 2") == Base::UNKNOWN);

        CHECK(parseBaseOption(" o") == Base::UNKNOWN);
        CHECK(parseBaseOption(" oct") == Base::UNKNOWN);
        CHECK(parseBaseOption(" 8") == Base::UNKNOWN);

        CHECK(parseBaseOption(" d") == Base::UNKNOWN);
        CHECK(parseBaseOption(" dec") == Base::UNKNOWN);
        CHECK(parseBaseOption(" 10") == Base::UNKNOWN);

        CHECK(parseBaseOption(" h") == Base::UNKNOWN);
        CHECK(parseBaseOption(" hex") == Base::UNKNOWN);
        CHECK(parseBaseOption(" 16") == Base::UNKNOWN);

        CHECK(parseBaseOption("b ") == Base::UNKNOWN);
        CHECK(parseBaseOption("bin ") == Base::UNKNOWN);
        CHECK(parseBaseOption("2 ") == Base::UNKNOWN);

        CHECK(parseBaseOption("o ") == Base::UNKNOWN);
        CHECK(parseBaseOption("oct ") == Base::UNKNOWN);
        CHECK(parseBaseOption("8 ") == Base::UNKNOWN);

        CHECK(parseBaseOption("d ") == Base::UNKNOWN);
        CHECK(parseBaseOption("dec ") == Base::UNKNOWN);
        CHECK(parseBaseOption("10 ") == Base::UNKNOWN);

        CHECK(parseBaseOption("h ") == Base::UNKNOWN);
        CHECK(parseBaseOption("hex ") == Base::UNKNOWN);
        CHECK(parseBaseOption("16 ") == Base::UNKNOWN);
    }

    SECTION("Empty Input") {
        CHECK(parseBaseOption("") == Base::UNKNOWN);
    }
}

// Prefix parsing only cares about the first two characters.
TEST_CASE("Parse Binary Prefix","[parse][prefix][binary]") {
    CHECK(detectPrefix("0b123") == BasePrefix::BIN);
    CHECK(detectPrefix("0b2342186") == BasePrefix::BIN);
    CHECK(detectPrefix("0b10110110") == BasePrefix::BIN);
    CHECK(detectPrefix("0b") == BasePrefix::BIN);
    CHECK(detectPrefix("0bINVALIDDATA") == BasePrefix::BIN);
}

TEST_CASE("Parse Octal Prefix","[parse][prefix][octal]") {
    CHECK(detectPrefix("0o123") == BasePrefix::OCT);
    CHECK(detectPrefix("0o21314765") == BasePrefix::OCT);
    CHECK(detectPrefix("0o123094983468") == BasePrefix::OCT);
    CHECK(detectPrefix("0o") == BasePrefix::OCT);
    CHECK(detectPrefix("0oINVALIDDATA") == BasePrefix::OCT);
}

TEST_CASE("Parse Hexadecimal Prefix","[parse][prefix][hex]") {
    CHECK(detectPrefix("0x123") == BasePrefix::HEX);
    CHECK(detectPrefix("0x12323484729847") == BasePrefix::HEX);
    CHECK(detectPrefix("0x123FFGHDJLKJER") == BasePrefix::HEX);
    CHECK(detectPrefix("0x") == BasePrefix::HEX);
    CHECK(detectPrefix("0xINVALIDDATA") == BasePrefix::HEX);
}

TEST_CASE("Parse No Prefix","[parse][prefix][decimal]") {

    SECTION("Short input") {
        CHECK(detectPrefix("") == BasePrefix::NONE);
        CHECK(detectPrefix("0") == BasePrefix::NONE);
        CHECK(detectPrefix("5") == BasePrefix::NONE);
        CHECK(detectPrefix("F") == BasePrefix::NONE);
        CHECK(detectPrefix("b") == BasePrefix::NONE);
        CHECK(detectPrefix("o") == BasePrefix::NONE);
        CHECK(detectPrefix("x") == BasePrefix::NONE);
    }

    SECTION("Non-Zero starter") {
        CHECK(detectPrefix("123") == BasePrefix::NONE);
        CHECK(detectPrefix("1232342186") == BasePrefix::NONE);
        CHECK(detectPrefix("123") == BasePrefix::NONE);
        CHECK(detectPrefix("1b") == BasePrefix::NONE);
        CHECK(detectPrefix("1o") == BasePrefix::NONE);
        CHECK(detectPrefix("1x") == BasePrefix::NONE);
    }

    SECTION("Zero-Leading Raw Numbers") {
        CHECK(detectPrefix("00") == BasePrefix::NONE);
        CHECK(detectPrefix("00INVALIDDATA") == BasePrefix::NONE);
        CHECK(detectPrefix("010101010011") == BasePrefix::NONE);
        CHECK(detectPrefix("073242346533") == BasePrefix::NONE);
        CHECK(detectPrefix("091321236576") == BasePrefix::NONE);
        CHECK(detectPrefix("0FC1563AA323") == BasePrefix::NONE);
    }
}

TEST_CASE("Parse Unknown Prefix","[parse][prefix][invalid]") {
    CHECK(detectPrefix("0d123") == BasePrefix::UNKNOWN);
    CHECK(detectPrefix("0p") == BasePrefix::UNKNOWN);
}

TEST_CASE("Base to Int Parsing", "[parse]") {
    CHECK(parseBaseToInt(Base::BIN) == 2);
    CHECK(parseBaseToInt(Base::OCT) == 8);
    CHECK(parseBaseToInt(Base::DEC) == 10);
    CHECK(parseBaseToInt(Base::HEX) == 16);

    // Should never naturally occur, but should return default base10.
    CHECK(parseBaseToInt(Base::UNKNOWN) == 10);
}
