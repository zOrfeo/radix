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
    format inFmt = format::DEC,outFmt = format::DEC;
    bool autoDetectinFmt = true;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                inFmt = parseOptarg(optarg);
                if (inFmt == format::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                autoDetectinFmt = false;
                break;
            case 'o':
                outFmt = parseOptarg(optarg);
                if (outFmt == format::UNK) {
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

    if (autoDetectinFmt) {
        inFmt = detectType(inputNum);

        if (inFmt != format::DEC) inputNum = inputNum.substr(2);
    }

    // Validate Input
    int validationRC = validateInput(inputNum, inFmt);

    if (validationRC != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(inFmt)] << " >> " << inputNum << std::endl;
        return validationRC;
    }

    if (inFmt == outFmt) {
        std::cout << inputNum << std::endl;
    }
    return ALL_OK;
}
