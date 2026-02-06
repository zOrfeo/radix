#include "numericFMT.h"
#include <string>
#include <unordered_map>
#include "constants.h"

numericFMT parseTypeOption(const std::string& typeString) {

    static const std::unordered_map<std::string, numericFMT> baseLookup = {
        {"h",   numericFMT::HEX},
        {"hex", numericFMT::HEX},
        {"16",  numericFMT::HEX},

        {"d",   numericFMT::DEC},
        {"dec", numericFMT::DEC},
        {"10",  numericFMT::DEC},

        {"o",   numericFMT::OCT},
        {"oct", numericFMT::OCT},
        {"8",   numericFMT::OCT},

        {"b",   numericFMT::BIN},
        {"bin", numericFMT::BIN},
        {"2",   numericFMT::BIN},
    };

    if (auto format = baseLookup.find(typeString); format != baseLookup.end()) return format->second;

    return numericFMT::UNK;
}

numericFMT detectType(const std::string& inputNum) {

    if (inputNum[0] != CHAR_ZERO) return numericFMT::DEC;

    switch(inputNum[1]) {
        case 'b': return numericFMT::BIN;
        case 'o': return numericFMT::OCT;
        case 'x': return numericFMT::HEX;
        default:  return numericFMT::DEC;
    }
}
