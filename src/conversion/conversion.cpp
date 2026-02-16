#include <string>
#include <algorithm>
#include "constants.h"
#include "parsing/parsing.h"
#include "base.h"
#include <climits>

int convertFromBase(const std::string& inputNum, const Base base) {
    int baseVal = parseBaseToInt(base);

    int decimalNumber = 0;
    int digit;
    for (char c : inputNum) {
        if (c >= CHAR_ZERO && c <= CHAR_NINE) {
            digit = c - CHAR_ZERO;
        } else {
            digit = c - CHAR_A + 10;
        }

        if (decimalNumber > (INT_MAX - digit) / baseVal ) return INT_MAX;

        decimalNumber *= baseVal;
        decimalNumber += digit;
    }

    return decimalNumber;
};

std::string convertToBase(int decimalNumber, const Base base) {
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
