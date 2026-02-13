#include "base.h"
#include <string>
#include <unordered_map>
#include "constants.h"

Base parseBaseOption(const std::string& typeString) {

    static const std::unordered_map<std::string, Base> baseLookup = {
        {"h",   Base::HEXADECIMAL},
        {"hex", Base::HEXADECIMAL},
        {"16",  Base::HEXADECIMAL},

        {"d",   Base::DECIMAL},
        {"dec", Base::DECIMAL},
        {"10",  Base::DECIMAL},

        {"o",   Base::OCTAL},
        {"oct", Base::OCTAL},
        {"8",   Base::OCTAL},

        {"b",   Base::BINARY},
        {"bin", Base::BINARY},
        {"2",   Base::BINARY},
    };

    if (auto base = baseLookup.find(typeString); base != baseLookup.end()) return base->second;

    return Base::UNKNOWN;
}

BasePrefix detectPrefix(const std::string& inputNum) {
    if (inputNum.size() < 2) return BasePrefix::NONE;

    if  (inputNum[0] != CHAR_ZERO) return BasePrefix::NONE;

    switch(inputNum[1]) {
        case CHAR_b: return BasePrefix::BINARY;
        case CHAR_o: return BasePrefix::OCTAL;
        case CHAR_x: return BasePrefix::HEXADECIMAL;
    }

    if (inputNum[1] >= CHAR_ZERO && inputNum[1] <= CHAR_NINE) {
        return BasePrefix::NONE;
    } else {
        return BasePrefix::UNKNOWN;
    }
}

int parseBaseToInt(const Base base) {
    switch(base) {
        case Base::BINARY: return BASE_BINARY;
        case Base::OCTAL: return BASE_OCTAL;
        case Base::HEXADECIMAL: return BASE_HEXADECIMAL;
        default: return BASE_DECIMAL;
    }
}
