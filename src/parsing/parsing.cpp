#include "base.h"
#include <string>
#include <unordered_map>
#include "ascii_constants.h"
#include "sign.h"

Base parseBaseOption(const std::string& typeString) {

    static const std::unordered_map<std::string, Base> baseLookup = {
        {"h",   Base::HEX},
        {"hex", Base::HEX},
        {"16",  Base::HEX},

        {"d",   Base::DEC},
        {"dec", Base::DEC},
        {"10",  Base::DEC},

        {"o",   Base::OCT},
        {"oct", Base::OCT},
        {"8",   Base::OCT},

        {"b",   Base::BIN},
        {"bin", Base::BIN},
        {"2",   Base::BIN},
    };

    if (auto base = baseLookup.find(typeString); base != baseLookup.end()) return base->second;

    return Base::UNKNOWN;
}

Sign detectSign(const std::string& inputNum) {
    if (inputNum[0] == '-') {
        return Sign::NEGATIVE;;
    } else if(inputNum[0] == '+') {
        return Sign::POSITIVE;
    } else {
        return Sign::NONE;
    }
}

BasePrefix detectPrefix(const std::string& inputNum) {
    /*
     * Prefix detection follows the following logic:
     * - All prefixes are 2 characters long.
     * - All prefixes start with a 0.
     * - Numbers cannot only be a prefix.
     * - Prefixes are optional.
     * - If provided, prefixes should be valid.
     */
    if (inputNum.size() <= 2) return BasePrefix::NONE;

    if  (inputNum[0] != CHAR_ZERO) return BasePrefix::NONE;

    switch(inputNum[1]) {
        case CHAR_B_LOWER: return BasePrefix::BIN;
        case CHAR_O_LOWER: return BasePrefix::OCT;
        case CHAR_X_LOWER: return BasePrefix::HEX;
    }

    if (inputNum[1] < DEC_MIN || inputNum[1] > DEC_MAX) {
        if (inputNum[1] < HEX_MIN_UPPER || inputNum[1] > HEX_MAX_UPPER) {
            return BasePrefix::UNKNOWN;
        } else {
            return BasePrefix::NONE;
        }
    } else {
        return BasePrefix::NONE;
    }
}
