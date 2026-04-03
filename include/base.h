#ifndef FORMAT_H
#define FORMAT_H

#include <cstdint>

enum class Base {
    BIN = 2,
    OCT = 8,
    DEC = 10,
    HEX = 16,
    UNKNOWN
};

enum class BasePrefix {
    BIN,
    OCT,
    DEC,
    HEX,
    UNKNOWN,
    NONE
};

#endif
