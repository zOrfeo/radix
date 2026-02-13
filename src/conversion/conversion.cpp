#include <string>
#include "constants.h"
#include "parsing/parsing.h"

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

std::string convertToBase(const int decimalNumber, const Base base) {
    return "";
};
