#include <string>
#include <algorithm>
#include "ascii_constants.h"
#include "base.h"
#include <cstdint>
#include <utility>

constexpr std::uint64_t UINT64_MAX_DIV10 = UINT64_MAX / 10;
constexpr std::uint8_t UINT64_MAX_LSD = UINT64_MAX % 10;

std::uint64_t convertFromBase(const std::string& inputNum, const Base base) {
    std::uint8_t baseVal = std::to_underlying(base);

    std::uint64_t decimalNumber = 0;
    std::uint8_t digit;
    for (char c : inputNum) {
        if (c >= DEC_MIN && c <= DEC_MAX) {
            digit = c - NUM_OFFSET;
        } else if (c >= HEX_MIN_UPPER && c <= HEX_MAX_UPPER) {
            digit = c - HEX_OFFSET_UPPER;
        } else {
            digit = c - HEX_OFFSET_LOWER;
        }

        if (decimalNumber >= (UINT64_MAX - digit) / baseVal ) return UINT64_MAX;

        decimalNumber *= baseVal;
        decimalNumber += digit;
    }

    return decimalNumber;
};

std::string convertToBase(std::uint64_t decimalNumber, const Base base) {
    if (decimalNumber == 0) return "0";

    std::uint8_t baseVal = std::to_underlying(base);

    std::string nonDecimalNumber = "";
    nonDecimalNumber.reserve(32);

    while (decimalNumber > 0) {
        std::uint8_t remainder = decimalNumber % baseVal;

        if (remainder <= 9) {
            nonDecimalNumber += static_cast<char>(remainder + NUM_OFFSET);
        } else {
            nonDecimalNumber += static_cast<char>(remainder + HEX_OFFSET_UPPER);
        }

        decimalNumber /= baseVal;
    }

    std::reverse(nonDecimalNumber.begin(),nonDecimalNumber.end());
    return nonDecimalNumber;
};

std::uint64_t stringToUInt64(const std::string& string) {
    std::uint64_t num = 0;

    for (char c : string) {
        if ( num > UINT64_MAX_DIV10 || ( num == UINT64_MAX_DIV10 && (c - NUM_OFFSET) >= UINT64_MAX_LSD )) {
            return UINT64_MAX;
        }

        num *= 10;
        num += (c - NUM_OFFSET);
    }
    return num;
}
