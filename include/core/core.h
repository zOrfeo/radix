#ifndef CORE_H
#define CORE_H

#include <getopt.h>
#include <unistd.h>
#include <string>
#include "base.h"
#include <unistd.h>

std::pair<int, std::string> processInput(std::string& inputNum, Base inBase, Base outBase);

constexpr std::string_view buildPrefix(Base base) {
    switch (base) {
        case Base::BIN: return "0b";
        case Base::OCT: return "0o";
        case Base::HEX: return "0x";
        default: return "";
    }
}

#endif
