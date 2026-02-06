#include <string>
#include "constants.h"
#include "format.h"

int validateInput(std::string& inputNum, format fmt) {
    if (fmt == format::BIN) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_ONE) {return INVLD_FMT_ERR;}
        }
        return ALL_OK;
    }

    if (fmt == format::OCT) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_SEVEN) {return INVLD_FMT_ERR;}
        }
        return ALL_OK;
    }

    if (fmt == format::DEC) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {return INVLD_FMT_ERR;}
        }
        return ALL_OK;
    }

    if (fmt == format::HEX) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);

            if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {
               if (charOrd < CHAR_A || charOrd > CHAR_F ) {return INVLD_FMT_ERR;}
            }
        }
        return ALL_OK;
    }

    return INVLD_FMT_ERR;
};
