#include <string>
#include <iostream>
#include "constants.h"

void errMsg(const int errCode, const std::string& message) {
    switch (errCode) {
        case INVLD_OPT_ERR: std::cerr << "Invalid Option {"; break;
        case INVLD_ARG_ERR: std::cerr << "Invalid Option Argument {"; break;
        case INVLD_PFX_ERR: std::cerr << "Invalid Prefix {"; break;
        case INVLD_NUM_ERR: std::cerr << "Invalid Input Number {"; break;
        default: std::cerr << "Unknown Error {"; break;
    }

    std::cerr << message << "}" << std::endl;
}
