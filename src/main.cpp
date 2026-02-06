#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>
#include "numericFMT.h"
#include "parsing/parsing.h"
#include "validation/validation.h"
#include "constants.h"

int main (int argc, char *argv[]) {
    int opt;
    numericFMT sfmt,tfmt;
    bool autoDetectSfmt = true;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch(opt) {
            case 'i':
                sfmt = parseTypeOption(optarg);
                if (sfmt == numericFMT::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                autoDetectSfmt = false;
                break;
            case 'o':
                tfmt = parseTypeOption(optarg);
                if (tfmt == numericFMT::UNK) {
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

    if (autoDetectSfmt) {
        sfmt = detectType(inputNum);

        if (sfmt != numericFMT::DEC) inputNum = inputNum.substr(2);
    }

    // Validate Input
    int validationRC = validateInput(inputNum, sfmt);

    if (validationRC != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(sfmt)] << " >> " << inputNum << std::endl;
        return validationRC;
    }

    if (sfmt == tfmt) {
        std::cout << inputNum << std::endl;
    }
    return ALL_OK;
}
