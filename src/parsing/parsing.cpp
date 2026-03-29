#include "base.h"
#include <string>
#include <unordered_map>
#include "constants.h"

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

BasePrefix detectPrefix(const std::string& inputNum) {
    if (inputNum.size() <= 2) return BasePrefix::NONE;

    if  (inputNum[0] != CHAR_ZERO) return BasePrefix::NONE;

    switch(inputNum[1]) {
        case CHAR_b: return BasePrefix::BIN;
        case CHAR_o: return BasePrefix::OCT;
        case CHAR_x: return BasePrefix::HEX;
    }

    if (inputNum[1] < CHAR_ZERO || inputNum[1] > CHAR_NINE) {
        if (inputNum[1] < CHAR_A || inputNum[1] > CHAR_F) {
            return BasePrefix::UNKNOWN;
        } else {
            return BasePrefix::NONE;
        }
    } else {
        return BasePrefix::NONE;
    }
}
