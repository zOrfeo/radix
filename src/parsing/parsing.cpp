#include "numericFMT.h"
#include <string>

numericFMT parseType(std::string typeString) {
    if (typeString == "h" ) return numericFMT::HEX;
    if (typeString == "d" ) return numericFMT::DEC;
    if (typeString == "o" ) return numericFMT::OCT;
    if (typeString == "b" ) return numericFMT::BIN;
    return numericFMT::UNK;
}
