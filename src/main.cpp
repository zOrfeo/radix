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
    if (argc != EXPCTD_ARG_CNT + 1) {
        std::cerr << "Incorrect number of arguments passed (" << argc << ")" << std::endl;
        return INVLD_ARG_CNT_ERR;
    }
    int opt;
    numericFMT sfmt,tfmt;
    std::string inputNum;

    // GetOpts
    while ((opt = getopt(argc, argv, "s:t:n:")) != -1) {
        switch(opt) {
            case 's':
                sfmt = parseType(optarg);
                if (sfmt == numericFMT::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                break;
            case 't':
                tfmt = parseType(optarg);
                if (tfmt == numericFMT::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                break;
            case 'n':
                inputNum = optarg;
                break;
            default:
                std::cerr << "Unknown option {" << optarg << "}" << std::endl;
                return INVLD_ARG_ERR;
        }
    }

    // Validate Input
    int rc = validateInput(inputNum, sfmt);

    if (rc != ALL_OK) {
        const char* numberTypeStrings[] = { "BINARY", "OCTAL", "DECIMAL", "HEXADECIMAL", "UNKNOWN" };
        std::cerr << "Invalid " << numberTypeStrings[static_cast<int>(sfmt)] << " >> " << inputNum << std::endl;
        return rc;
    }

    if (sfmt == tfmt) {
        std::cout << inputNum << std::endl;
    }
    return ALL_OK;
}
