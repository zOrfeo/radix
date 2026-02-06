#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>
#include "format.h"
#include "parsing/parsing.h"
#include "validation/validation.h"
#include "constants.h"

int main (int argc, char *argv[]) {
    int opt;
    format iBase = format::DEC,oBase = format::DEC;
    bool autoDetectIBase = true;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                iBase = parseOptarg(optarg);
                if (iBase == format::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                autoDetectIBase = false;
                break;
            case 'o':
                oBase = parseOptarg(optarg);
                if (oBase == format::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                break;
            default:
                std::cerr << "Unknown option {" << optarg << "}" << std::endl;
                return INVLD_ARG_ERR;
        }
    }
    std::string inputNum = argv[argc-1];

    if (autoDetectIBase) {
        iBase = detectType(inputNum);

        if (iBase != format::DEC) inputNum = inputNum.substr(2);
    }

    // Validate Input
    int validationRC = validateInput(inputNum, iBase);

    if (validationRC != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(iBase)] << " >> " << inputNum << std::endl;
        return validationRC;
    }

    if (iBase == oBase) {
        std::cout << inputNum << std::endl;
    }
    return ALL_OK;
}
