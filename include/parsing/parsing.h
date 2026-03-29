#ifndef PARSING_H
#define PARSING_H

#include <string>
#include "base.h"
#include "constants.h"

Base parseBaseOption(const std::string& typeString);
BasePrefix detectPrefix(const std::string& inputNum);

constexpr int parseBaseToInt(const Base base) {
    switch(base) {
        case Base::BIN: return BASE_BIN;
        case Base::OCT: return BASE_OCT;
        case Base::HEX: return BASE_HEX;
        default: return BASE_DEC;
    }
}

#endif
