#include <cstdint>

// ASCII character codes
constexpr int CHAR_ZERO  = 48;
constexpr int CHAR_ONE   = 49;
constexpr int CHAR_SEVEN = 55;
constexpr int CHAR_NINE  = 57;
constexpr int CHAR_A     = 65;
constexpr int CHAR_F     = 70;
constexpr int CHAR_b     = 98;
constexpr int CHAR_o     = 111;
constexpr int CHAR_x     = 120;

// Return Codes
constexpr int ALL_OK        = 0;
constexpr int INVLD_OPT_ERR = 1;
constexpr int INVLD_ARG_ERR = 2;
constexpr int INVLD_PFX_ERR = 3;
constexpr int INVLD_NUM_ERR = 4;

// Bases
constexpr int BASE_BIN = 2;
constexpr int BASE_OCT = 8;
constexpr int BASE_DEC = 10;
constexpr int BASE_HEX = 16;

// Generic Constants
constexpr std::uint32_t UINT32_DIV10 = UINT32_MAX / 10;
constexpr std::uint32_t UINT32_LSD = UINT32_MAX % 10;
