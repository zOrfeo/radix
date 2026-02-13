#include <string>
#include "constants.h"
#include "base.h"

int validateBinary(std::string& inputNum) {
    for (char c : inputNum) {
        int charOrd = static_cast<int>(c);
        if (charOrd < CHAR_ZERO || charOrd > CHAR_ONE) {return INVLD_FMT_ERR;}
    }
    return ALL_OK;
};

int validateOctal(std::string& inputNum) {
    for (char c : inputNum) {
        int charOrd = static_cast<int>(c);
        if (charOrd < CHAR_ZERO || charOrd > CHAR_SEVEN) {return INVLD_FMT_ERR;}
    }
    return ALL_OK;
};

int validateDecimal(std::string& inputNum) {
    for (char c : inputNum) {
        int charOrd = static_cast<int>(c);
        if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {return INVLD_FMT_ERR;}
    }
    return ALL_OK;
};

int validateHexadecimal(std::string& inputNum) {
    for (char c : inputNum) {
        int charOrd = static_cast<int>(c);

        if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {
            if (charOrd < CHAR_A || charOrd > CHAR_F ) {return INVLD_FMT_ERR;}
        }
    }
    return ALL_OK;
};
