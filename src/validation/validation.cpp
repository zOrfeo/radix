#include <string>
#include "ascii_constants.h"
#include "base.h"

bool validateBinary(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < BIN_MIN || c > BIN_MAX) {return false;}
    }
    return true;
}

bool validateOctal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < OCT_MIN || c > OCT_MAX) {return false;}
    }
    return true;
}

bool validateDecimal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < DEC_MIN || c > DEC_MAX) {return false;}
    }
    return true;
}

bool validateHexadecimal(const std::string& inputNum) {
    for (char c : inputNum) {
        if (c < DEC_MIN || c > DEC_MAX) {
            if (c < HEX_MIN || c > HEX_MAX ) {return false;}
        }
    }
    return true;
}

bool validateInput(const std::string& inputNum, Base base) {
    switch (base) {
        case Base::BIN: return validateBinary(inputNum);
        case Base::OCT: return validateOctal(inputNum);
        case Base::HEX: return validateHexadecimal(inputNum);
        default: return validateDecimal(inputNum);
    }
}
