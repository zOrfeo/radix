#include <catch2/catch_test_macros.hpp>
#include "core/core.h"
#include "base.h"
#include "constants.h"

TEST_CASE("Build Prefix", "[core][prefix]") {
    CHECK(buildPrefix(Base::BIN) == "0b");
    CHECK(buildPrefix(Base::OCT) == "0o");
    CHECK(buildPrefix(Base::DEC) == "");
    CHECK(buildPrefix(Base::HEX) == "0x");
    CHECK(buildPrefix(Base::UNKNOWN) == "");
}

TEST_CASE("Process Binary Input", "[core][binary]") {
    std::string inputBinary = "11111111";
    CHECK(processInput(inputBinary, Base::BIN, Base::BIN).second == "11111111");
    CHECK(processInput(inputBinary, Base::BIN, Base::OCT).second == "377");
    CHECK(processInput(inputBinary, Base::BIN, Base::DEC).second == "255");
    CHECK(processInput(inputBinary, Base::BIN, Base::HEX).second == "FF");
}

TEST_CASE("Process Octal Input", "[core][octal]") {
    std::string inputOctal = "377";
    CHECK(processInput(inputOctal, Base::OCT, Base::BIN).second == "11111111");
    CHECK(processInput(inputOctal, Base::OCT, Base::OCT).second == "377");
    CHECK(processInput(inputOctal, Base::OCT, Base::DEC).second == "255");
    CHECK(processInput(inputOctal, Base::OCT, Base::HEX).second == "FF");
}

TEST_CASE("Process Decimal Input", "[core][decimal]") {
    std::string inputDecimal = "255";
    CHECK(processInput(inputDecimal, Base::DEC, Base::BIN).second == "11111111");
    CHECK(processInput(inputDecimal, Base::DEC, Base::OCT).second == "377");
    CHECK(processInput(inputDecimal, Base::DEC, Base::DEC).second == "255");
    CHECK(processInput(inputDecimal, Base::DEC, Base::HEX).second == "FF");
}

TEST_CASE("Process Hex Input", "[core][hex]") {
    std::string inputHex = "FF";
    CHECK(processInput(inputHex, Base::HEX, Base::BIN).second == "11111111");
    CHECK(processInput(inputHex, Base::HEX, Base::OCT).second == "377");
    CHECK(processInput(inputHex, Base::HEX, Base::DEC).second == "255");
    CHECK(processInput(inputHex, Base::HEX, Base::HEX).second == "FF");
}

TEST_CASE("Prefix Overrides", "[core][error]") {
    std::string inputNum = "0b11111111";
    CHECK(processInput(inputNum, Base::DEC, Base::DEC).second == "255");

    inputNum = "0o377";
    CHECK(processInput(inputNum, Base::BIN, Base::DEC).second == "255");

    inputNum = "0xFF";
    CHECK(processInput(inputNum, Base::OCT, Base::DEC).second == "255");
}

TEST_CASE("Error Scenarios", "[core][error]") {
    SECTION("Invalid Prefixes") {
        std::string inputNum = "0z123";
        CHECK(processInput(inputNum, Base::DEC, Base::OCT).first == INVLD_PFX_ERR);
        CHECK(processInput(inputNum, Base::DEC, Base::OCT).second == "0z123");

        inputNum = "0q777";
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).first == INVLD_PFX_ERR);
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).second == "0q777");

        inputNum = "0p1010";
        CHECK(processInput(inputNum, Base::OCT, Base::BIN).first == INVLD_PFX_ERR);
        CHECK(processInput(inputNum, Base::OCT, Base::BIN).second == "0p1010");
    }
    SECTION("Invalid Binary Numbers") {
        std::string inputNum = "10201";
        CHECK(processInput(inputNum, Base::BIN, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::BIN, Base::DEC).second == "10201");

        inputNum = "0b10201";
        CHECK(processInput(inputNum, Base::BIN, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::BIN, Base::DEC).second == "10201");
    }

    SECTION("Invalid Octal Numbers") {
        std::string inputNum = "789";
        CHECK(processInput(inputNum, Base::OCT, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::OCT, Base::DEC).second == "789");

        inputNum = "0o789";
        CHECK(processInput(inputNum, Base::OCT, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::OCT, Base::DEC).second == "789");
    }

    SECTION("Invalid Decimal Numbers") {
        std::string inputNum = "12A3";
        CHECK(processInput(inputNum, Base::DEC, Base::HEX).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::DEC, Base::HEX).second == "12A3");

        inputNum = "999X";
        CHECK(processInput(inputNum, Base::DEC, Base::HEX).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::DEC, Base::HEX).second == "999X");
    }

    SECTION("Invalid Hex Numbers") {
        std::string inputNum = "FG";
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).second == "FG");

        inputNum = "0xFG";
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).first == INVLD_NUM_ERR);
        CHECK(processInput(inputNum, Base::HEX, Base::DEC).second == "FG");
    }
}
