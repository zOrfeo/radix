#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>
#include "base.h"
#include "parsing/parsing.h"
#include "validation/validation.h"
#include "constants.h"
#include "conversion/conversion.h"

int main (int argc, char *argv[]) {
    int opt;
    Base inBase = Base::DEC,outBase = Base::DEC;
    bool srcFlagSet = false, applyOutputPrefix=false;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:p")) != -1) {
        switch(opt) {
            case 'i':
                inBase = parseBaseOption(optarg);
                if (inBase == Base::UNKNOWN) {
                    std::cerr << "Unknown base {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                srcFlagSet = true;
                break;

            case 'o':
                outBase = parseBaseOption(optarg);
                if (outBase == Base::UNKNOWN) {
                    std::cerr << "Unknown base {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                break;

            case 'p':
                applyOutputPrefix = true;
                break;

            default:
                std::cerr << "Unknown option {" << optarg << "}" << std::endl;
                return INVLD_OPT_ERR;
        }
    }
    std::string inputNum = argv[argc-1];

    // Prefix Handling
    BasePrefix prefix = detectPrefix(inputNum);

    if (prefix == BasePrefix::UNKNOWN) {
        std::cerr << "Invalid Prefix " << inputNum.substr(0,2) << std::endl;
        return INVLD_PFX_ERR;
    }

    if (prefix != BasePrefix::NONE) inputNum = inputNum.substr(2);

    if (!srcFlagSet) {
        switch (prefix) {
            case BasePrefix::BIN: inBase = Base::BIN;
                break;

            case BasePrefix::OCT: inBase = Base::OCT;
                break;

            case BasePrefix::HEX: inBase = Base::HEX;
                break;

            default: inBase = Base::DEC;
        }
    }

    // Validate Input
    int validationRC;
    switch (inBase) {
        case Base::BIN: validationRC = validateBinary(inputNum);
            break;

        case Base::OCT: validationRC = validateOctal(inputNum);
            break;

        case Base::HEX: validationRC = validateHexadecimal(inputNum);
            break;

        default: validationRC = validateDecimal(inputNum);
    }

    if (validationRC != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(inBase)] << " >> " << inputNum << std::endl;
        return validationRC;
    }

    // Conversion & Output
    if (inBase == outBase) {
        std::cout << inputNum << std::endl;
        return ALL_OK;
    }

    int decimalNumber;
    if (inBase != Base::DEC){
        decimalNumber = convertFromBase(inputNum,inBase);
    } else {
        decimalNumber = stoi(inputNum);
    }

    std::string outputNumber;
    if (outBase != Base::DEC) {
        outputNumber = convertToBase(decimalNumber,outBase);
    } else {
        outputNumber = std::to_string(decimalNumber);
    }

    std::string outPrefix = "";
    if (applyOutputPrefix) {
        switch (outBase) {
            case Base::BIN: outPrefix = "0b";
                break;

            case Base::OCT: outPrefix = "0o";
                break;

            case Base::HEX: outPrefix = "0x";
                break;

            default: outPrefix = "";
        }
    }
    std::cout << outPrefix << outputNumber << std::endl;
    return ALL_OK;
}
