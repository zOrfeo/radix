#include <getopt.h>
#include <unistd.h>
#include <string>
#include "base.h"
#include "parsing/parsing.h"
#include "constants.h"
#include "validation/validation.h"
#include "conversion/conversion.h"
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

    std::uint32_t decimalNumber;
    if (inBase != Base::DEC){
        decimalNumber = convertFromBase(inputNum,inBase);
    } else {
        decimalNumber = stringToUInt32(inputNum);
    }

    if (outBase != Base::DEC) {
        return {ALL_OK,convertToBase(decimalNumber,outBase)};
    } else {
        return {ALL_OK,std::to_string(decimalNumber)};
    }
}
