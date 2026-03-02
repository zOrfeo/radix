#include <string>
#include "constants.h"

bool validateBinary(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_ONE) {return false;}
    }
    return true;
};

bool validateOctal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_SEVEN) {return false;}
    }
    return true;
};

bool validateDecimal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_NINE) {return false;}
    }
    return true;
};

bool validateHexadecimal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_NINE) {
            if (c < CHAR_A || c > CHAR_F ) {return false;}
        }
    }
    return true;
};
