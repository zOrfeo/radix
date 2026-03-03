#include <string>
#include <algorithm>
#include "constants.h"
#include "parsing/parsing.h"
#include "base.h"
#include <cstdint>

std::uint32_t convertFromBase(const std::string& inputNum, const Base base) {
    std::uint32_t baseVal = parseBaseToInt(base);

    std::uint32_t decimalNumber = 0;
    std::uint32_t digit;
    for (char c : inputNum) {
        if (c >= CHAR_ZERO && c <= CHAR_NINE) {
            digit = c - CHAR_ZERO;
        } else {
            digit = c - CHAR_A + 10;
        }

        if (decimalNumber > (UINT32_MAX - digit) / baseVal ) return UINT32_MAX;

        decimalNumber *= baseVal;
        decimalNumber += digit;
    }

    return decimalNumber;
};

std::string convertToBase(std::uint32_t decimalNumber, const Base base) {
    if (decimalNumber == 0) return "0";

    int baseVal = parseBaseToInt(base);

    std::string nonDecimalNumber = "";
    nonDecimalNumber.reserve(32);

    while (decimalNumber > 0) {
        int remainder = decimalNumber % baseVal;

        if (remainder <= 9) {
            nonDecimalNumber += static_cast<char>(remainder + CHAR_ZERO);
        } else {
            nonDecimalNumber += static_cast<char>(remainder - 10 + CHAR_A);
        }

        decimalNumber /= baseVal;
    }

    std::reverse(nonDecimalNumber.begin(),nonDecimalNumber.end());
    return nonDecimalNumber;
};

std::uint32_t stringToUInt32(const std::string& string) {
    std::uint32_t num = 0;
    std::size_t slen = string.length();

    for (char c : string) {
        if ( num > UINT32_DIV10 || ( num == UINT32_DIV10 && (c - CHAR_ZERO) > UINT32_LSD )) {
            return UINT32_MAX;
        }

        num = ( num * 10 );
        num += (c - CHAR_ZERO);
    }
    return num;
}
