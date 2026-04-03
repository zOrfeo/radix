#include <string>
#include <algorithm>
#include "ascii_constants.h"
#include "base.h"
#include <cstdint>
#include <utility>

constexpr std::uint32_t UINT32_MAX_DIV10 = UINT32_MAX / 10;
constexpr std::uint8_t UINT32_MAX_LSD = UINT32_MAX % 10;

std::uint32_t convertFromBase(const std::string& inputNum, const Base base) {
    std::uint8_t baseVal = std::to_underlying(base);

    std::uint32_t decimalNumber = 0;
    std::uint8_t digit;
    for (char c : inputNum) {
        if (c >= DEC_MIN && c <= DEC_MAX) {
            digit = c - NUM_OFFSET;
        } else {
            digit = c - HEX_OFFSET;
        }

        if (decimalNumber >= (UINT32_MAX - digit) / baseVal ) return UINT32_MAX;

        decimalNumber *= baseVal;
        decimalNumber += digit;
    }

    return decimalNumber;
};

std::string convertToBase(std::uint32_t decimalNumber, const Base base) {
    if (decimalNumber == 0) return "0";

    std::uint8_t baseVal = std::to_underlying(base);

    std::string nonDecimalNumber = "";
    nonDecimalNumber.reserve(32);

    while (decimalNumber > 0) {
        std::uint8_t remainder = decimalNumber % baseVal;

        if (remainder <= 9) {
            nonDecimalNumber += static_cast<char>(remainder + NUM_OFFSET);
        } else {
            nonDecimalNumber += static_cast<char>(remainder + HEX_OFFSET);
        }

        decimalNumber /= baseVal;
    }

    std::reverse(nonDecimalNumber.begin(),nonDecimalNumber.end());
    return nonDecimalNumber;
};

std::uint32_t stringToUInt32(const std::string& string) {
    std::uint32_t num = 0;

    for (char c : string) {
        if ( num > UINT32_MAX_DIV10 || ( num == UINT32_MAX_DIV10 && (c - NUM_OFFSET) >= UINT32_MAX_LSD )) {
            return UINT32_MAX;
        }

        num *= 10;
        num += (c - NUM_OFFSET);
    }
    return num;
}
