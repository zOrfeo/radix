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
    Base inBase = Base::DECIMAL,outBase = Base::DECIMAL;
    bool srcFlagSet = false, applyOutputPrefix=false;;

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

    BasePrefix prfx = detectPrefix(inputNum);

    if (prfx == BasePrefix::UNKNOWN) {
        std::cerr << "Invalid Prefix " << inputNum.substr(0,2) << std::endl;
        return INVLD_PFX_ERR;
    }

    if (prfx != BasePrefix::NONE) inputNum = inputNum.substr(2);

    if (!srcFlagSet) {
        switch (prfx) {
            case BasePrefix::BINARY: inBase = Base::BINARY;
                break;

            case BasePrefix::OCTAL: inBase = Base::OCTAL;
                break;

            case BasePrefix::HEXADECIMAL: inBase = Base::HEXADECIMAL;
                break;

            default: inBase = Base::DECIMAL;
        }
    }

    // Validate Input
    int validationRC;
    switch (inBase) {
        case Base::BINARY: validationRC = validateBinary(inputNum);
            break;

        case Base::OCTAL: validationRC = validateOctal(inputNum);
            break;

        case Base::HEXADECIMAL: validationRC = validateHexadecimal(inputNum);
            break;

        default: validationRC = validateDecimal(inputNum);
    }

    if (validationRC != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(inBase)] << " >> " << inputNum << std::endl;
        return validationRC;
    }

    if (inBase == outBase) {
        std::cout << inputNum << std::endl;
        return ALL_OK;
    }

    int decimalNumber;
    if (inBase != Base::DECIMAL){
        decimalNumber = convertFromBase(inputNum,inBase);
    } else {
        decimalNumber = stoi(inputNum);
    }

    std::string outputNumber;
    if (outBase != Base::DECIMAL) {
        outputNumber = convertToBase(decimalNumber,outBase);
    } else {
        outputNumber = std::to_string(decimalNumber);
    }

    std::string outPrefix = "";
    if (applyOutputPrefix) {
        switch (outBase) {
            case Base::BINARY: outPrefix = "0b";
                break;

            case Base::OCTAL: outPrefix = "0o";
                break;

            case Base::HEXADECIMAL: outPrefix = "0x";
                break;

            default: outPrefix = "";
        }
    }
    std::cout << outPrefix << outputNumber << std::endl;
    return ALL_OK;
}
