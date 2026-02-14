#include <string>
#include "constants.h"

int validateBinary(std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_ONE) {return INVLD_NUM_ERR;}
    }
    return ALL_OK;
};

int validateOctal(std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_SEVEN) {return INVLD_NUM_ERR;}
    }
    return ALL_OK;
};

int validateDecimal(std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_NINE) {return INVLD_NUM_ERR;}
    }
    return ALL_OK;
};

int validateHexadecimal(std::string& inputNum) {
    for (char c : inputNum) {
        if (c < CHAR_ZERO || c > CHAR_NINE) {
            if (c < CHAR_A || c > CHAR_F ) {return INVLD_NUM_ERR;}
        }
    }
    return ALL_OK;
};
