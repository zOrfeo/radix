#include "format.h"
#include <string>
#include <unordered_map>
#include "constants.h"

format parseOptarg(const std::string& typeString) {

    static const std::unordered_map<std::string, format> baseLookup = {
        {"h",   format::HEX},
        {"hex", format::HEX},
        {"16",  format::HEX},

        {"d",   format::DEC},
        {"dec", format::DEC},
        {"10",  format::DEC},

        {"o",   format::OCT},
        {"oct", format::OCT},
        {"8",   format::OCT},

        {"b",   format::BIN},
        {"bin", format::BIN},
        {"2",   format::BIN},
    };

    if (auto format = baseLookup.find(typeString); format != baseLookup.end()) return format->second;

    return format::UNK;
}

format detectType(const std::string& inputNum) {

    if (inputNum[0] != CHAR_ZERO) return format::DEC;

    switch(inputNum[1]) {
        case 'b': return format::BIN;
        case 'o': return format::OCT;
        case 'x': return format::HEX;
        default:  return format::DEC;
    }
}
