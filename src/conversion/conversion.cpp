#include <string>
#include <algorithm>
#include "constants.h"
#include "parsing/parsing.h"
#include "base.h"

int convertFromBase(const std::string& inputNum, const Base base) {
    int baseVal = parseBaseToInt(base);

    int decimalNumber = 0;
    for (char c : inputNum) {
        decimalNumber *= baseVal;
        if (c >= CHAR_ZERO && c <= CHAR_NINE) {
            decimalNumber += c - CHAR_ZERO;
        } else {
            decimalNumber += c - CHAR_A + 10;
        }
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
