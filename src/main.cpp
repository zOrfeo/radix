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

numberType parseType(std::string typeString);

int main (int argc, char *argv[]) {
    if (argc < 6) {
        std::cout << "Too few arguments passed" << std::endl;
        return 1;
    }
    int opt;
    numberType sfmt,tfmt;
    std::string inputNum;

    while ((opt = getopt(argc, argv, "s:t:n:")) != -1) {
        switch(opt) {
            case 's':
                sfmt = parseType(optarg);
                break;
            case 't':
                tfmt = parseType(optarg);
                break;
            case 'n':
                inputNum = optarg;
                break;
            default:
                std::cout << "Unknown option {" << optarg << "}" << std::endl;
        }
    }

    if (sfmt == tfmt) {
        std::cout << inputNum << std::endl;
    }
    return 0;
}

numberType parseType(std::string typeString) {
    if (typeString == "h" ) return numberType::HEX;
    if (typeString == "d" ) return numberType::DEC;
    if (typeString == "o" ) return numberType::OCT;
    if (typeString == "b" ) return numberType::BIN;
    return numberType::UNK;
}
