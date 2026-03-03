#include <getopt.h>
#include <unistd.h>
#include <string>
#include "base.h"
#include "parsing/parsing.h"
#include "constants.h"
#include "validation/validation.h"
#include "conversion/conversion.h"
#include <climits>
#include <iostream>
#include <unistd.h>

std::pair<int, std::string> processInput(std::string& inputNum, Base inBase, Base outBase) {
    // Prefix Handling
    BasePrefix prefix = detectPrefix(inputNum);
    // Prefix overrides input flag
    switch (prefix) {
        case BasePrefix::BIN: inBase = Base::BIN; inputNum = inputNum.substr(2); break;
        case BasePrefix::OCT: inBase = Base::OCT; inputNum = inputNum.substr(2); break;
        case BasePrefix::HEX: inBase = Base::HEX; inputNum = inputNum.substr(2); break;
        case BasePrefix::UNKNOWN: return {INVLD_PFX_ERR,inputNum};
        default: break;
    }
    // Validate Input
    if (!validateInput(inputNum, inBase)) {
        return {INVLD_NUM_ERR,inputNum};
    }
    // Conversion & Output
    if (inBase == outBase) {
        return {ALL_OK,inputNum};
    }

    int decimalNumber;
    if (inBase != Base::DEC){
        decimalNumber = convertFromBase(inputNum,inBase);
    } else {
        try {
            decimalNumber = stoi(inputNum);
        } catch (const std::out_of_range& e) {
            decimalNumber = INT_MAX;
        }
    }

    std::string outputNumber;
    if (outBase != Base::DEC) {
        outputNumber = convertToBase(decimalNumber,outBase);
    } else {
        outputNumber = std::to_string(decimalNumber);
    }

    return {ALL_OK,outputNumber};
}

std::string buildPrefix(Base base) {
    switch (base) {
        case Base::BIN: return "0b";
        case Base::OCT: return "0o";
        case Base::HEX: return "0x";
        default: return "";
    }
}
