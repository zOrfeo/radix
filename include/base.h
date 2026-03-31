#ifndef FORMAT_H
#define FORMAT_H

enum class Base {
    BIN,
    OCT,
    DEC,
    HEX,
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

constexpr int BASE_BIN = 2;
constexpr int BASE_OCT = 8;
constexpr int BASE_DEC = 10;
constexpr int BASE_HEX = 16;

#endif
