#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>

enum class numberType {
    BIN,
    OCT,
    DEC,
    HEX,
    UNK // Unknown type
};

// ASCII character codes
constexpr int CHAR_ZERO  = 48;
constexpr int CHAR_ONE   = 49;
constexpr int CHAR_SEVEN = 55;
constexpr int CHAR_NINE  = 57;
constexpr int CHAR_A     = 65;
constexpr int CHAR_F     = 70;

// Return Codes
constexpr int ALL_OK            = 0;
constexpr int INVLD_ARG_CNT_ERR = 1;
constexpr int INVLD_ARG_ERR     = 2;
constexpr int INVLD_FMT_ERR     = 3;

numberType parseType(std::string typeString);

int main (int argc, char *argv[]) {
    if (argc < 6) {
        std::cerr << "Too few arguments passed" << std::endl;
        return INVLD_ARG_CNT_ERR;
    }
    int opt;
    numberType sfmt,tfmt;
    std::string inputNum;

    // GetOpts
    while ((opt = getopt(argc, argv, "s:t:n:")) != -1) {
        switch(opt) {
            case 's':
                sfmt = parseType(optarg);
                if (sfmt == numberType::UNK) {
                    std::cerr << "Unknown format option {" << optarg << "}" << std::endl;
                    return INVLD_ARG_ERR;
                }
                break;
            case 't':
                tfmt = parseType(optarg);
                if (tfmt == numberType::UNK) {
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
    if (sfmt == numberType::BIN) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_ONE) {std::cerr << "Invalid BINARY <" << inputNum << ">" << std::endl; return INVLD_FMT_ERR;}
        }
    }

    if (sfmt == numberType::OCT) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_SEVEN) {std::cerr << "Invalid OCTAL <" << inputNum << ">" << std::endl; return INVLD_FMT_ERR;}
        }
    }

    if (sfmt == numberType::DEC) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);
            if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {std::cerr << "Invalid DECIMAL <" << inputNum << ">" << std::endl; return INVLD_FMT_ERR;}
        }
    }

    if (sfmt == numberType::HEX) {
        for (char c : inputNum) {
            int charOrd = static_cast<int>(c);

            if (charOrd < CHAR_ZERO || charOrd > CHAR_NINE) {
               if (charOrd < CHAR_A || charOrd > CHAR_F ) {std::cerr << "Invalid HEXADECIMAL <" << inputNum << ">" << std::endl; return INVLD_FMT_ERR;}
            }
        }
    }

    if (sfmt == tfmt) {
        std::cout << inputNum << std::endl;
    }
    return ALL_OK;
}

numberType parseType(std::string typeString) {
    if (typeString == "h" ) return numberType::HEX;
    if (typeString == "d" ) return numberType::DEC;
    if (typeString == "o" ) return numberType::OCT;
    if (typeString == "b" ) return numberType::BIN;
    return numberType::UNK;
}
