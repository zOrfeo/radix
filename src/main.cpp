#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>
#include "base.h"
#include "parsing/parsing.h"
#include "return_codes.h"
#include "core/core.h"
#include <iostream>
#include <unistd.h>
#include "logging/logging.h"
#include "sign.h"

int main (int argc, char *argv[]) {
    int opt;
    Base inBase = Base::DEC, outBase = Base::DEC;
    bool applyOutputPrefix = false, applyOutputSign = false;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:ps")) != -1) {
        switch(opt) {
            case 'i':
                inBase = parseBaseOption(optarg);
                if (inBase == Base::UNKNOWN) {
                    errMsg(INVLD_ARG_ERR, optarg);
                    return INVLD_ARG_ERR;
                }
                break;

            case 'o':
                outBase = parseBaseOption(optarg);
                if (outBase == Base::UNKNOWN) {
                    errMsg(INVLD_ARG_ERR, optarg);
                    return INVLD_ARG_ERR;
                }
                break;

            case 'p':
                applyOutputPrefix = true;
                break;

            case 's':
                applyOutputSign = true;
                break;

            default:
                errMsg(INVLD_OPT_ERR, std::to_string(opt));
                return INVLD_OPT_ERR;
                break;
        }
    }

    std::string inputNum;
    if (isatty(STDIN_FILENO)) {
        // If stdin is tty, then input is the last argument.
        inputNum = argv[argc-1];
        Sign sign = detectSign(inputNum);
        if (sign != Sign::NONE) inputNum.erase(0,1);

        auto [rc, outputNum] = processInput(inputNum, inBase, outBase);

        if (rc != ALL_OK) {
            errMsg(rc,inputNum);
            return rc;
        }

        std::cout << (sign == Sign::NEGATIVE ? "-" : (applyOutputSign ? "+" : ""));
        std::cout << (applyOutputPrefix ? buildPrefix(outBase) : "");
        std::cout << outputNum << std::endl;
    } else {
        while (std::getline(std::cin, inputNum)) {
            Sign sign = detectSign(inputNum);
            if (sign != Sign::NONE) inputNum.erase(0,1);

            auto [rc, outputNum] = processInput(inputNum, inBase, outBase);

            if (rc != ALL_OK) {
                errMsg(rc,inputNum);
                return rc;
            }

            std::cout << (sign == Sign::NEGATIVE ? "-" : (applyOutputSign ? "+" : ""));
            std::cout << (applyOutputPrefix ? buildPrefix(outBase) : "");
            std::cout << outputNum << std::endl;
        }
    }
    return ALL_OK;
}
