#ifndef ASCII_CONSTANTS_H
#define ASCII_CONSTANTS_H

/*
 * Character Ranges
 */
constexpr char BIN_MIN    = '0';
constexpr char BIN_MAX    = '1';

constexpr char OCT_MIN    = '0';
constexpr char OCT_MAX    = '7';

constexpr char DEC_MIN    = '0';
constexpr char DEC_MAX    = '9';

// Can use DEC range for 0-9.
constexpr char HEX_MIN_UPPER = 'A';
constexpr char HEX_MIN_LOWER = 'a';
constexpr char HEX_MAX_UPPER = 'F';
constexpr char HEX_MAX_LOWER = 'f';

/*
 * Offsets
 */
constexpr char NUM_OFFSET = '0';
constexpr char HEX_OFFSET_UPPER = 'A' - 10;
constexpr char HEX_OFFSET_LOWER = 'a' - 10;

/*
 * Specifically Referenced Characters
 */
constexpr char CHAR_ZERO    = '0';
constexpr char CHAR_B_LOWER = 'b';
constexpr char CHAR_O_LOWER = 'o';
constexpr char CHAR_X_LOWER = 'x';

#endif
