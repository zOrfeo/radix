#include <getopt.h>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <string>
#include "base.h"
#include "parsing/parsing.h"
#include "constants.h"
#include "core/core.h"
#include <iostream>
#include <unistd.h>
#include "logging/logging.h"

int main (int argc, char *argv[]) {
    int opt;
    Base inBase = Base::DEC, outBase = Base::DEC;
    bool applyOutputPrefix = false;

    // GetOpts
    while ((opt = getopt(argc, argv, "i:o:p")) != -1) {
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
        auto [rc, outputNum] = processInput(inputNum, inBase, outBase);

        if (rc != ALL_OK) {
            errMsg(rc,inputNum);
            return rc;
        }

        std::cout << (applyOutputPrefix ? buildPrefix(outBase) : "") << outputNum << std::endl;
    } else {
        while (std::getline(std::cin, inputNum)) {
            auto [rc, outputNum] = processInput(inputNum, inBase, outBase);

            if (rc != ALL_OK) {
                errMsg(rc,inputNum);
                return rc;
            }

            std::cout << (applyOutputPrefix ? buildPrefix(outBase) : "") << outputNum << std::endl;
        }
    }
    return ALL_OK;
}
