#include <string>
#include "ascii_constants.h"
#include "base.h"
#include <cstdint>
#include <utility>
#include <unordered_map>

constexpr std::uint8_t bitWidthToOctWidth[] = {
    0,
    1, 1, 1,        // 1–3
    2, 2, 2,        // 4–6
    3, 3, 3,        // 7–9
    4, 4, 4,        // 10–12
    5, 5, 5,        // 13–15
    6, 6, 6,        // 16–18
    7, 7, 7,        // 19–21
    8, 8, 8,        // 22–24
    9, 9, 9,        // 25–27
    10,10,10,       // 28–30
    11,11,11,       // 31–33
    12,12,12,       // 34–36
    13,13,13,       // 37–39
    14,14,14,       // 40–42
    15,15,15,       // 43–45
    16,16,16,       // 46–48
    17,17,17,       // 49–51
    18,18,18,       // 52–54
    19,19,19,       // 55–57
    20,20,20,       // 58–60
    21,21,21,       // 61–63
    22              // 64
};

constexpr std::uint8_t bitWidthToHexWidth[] = {
    0,
    1, 1, 1, 1,        // 1–4
    2, 2, 2, 2,        // 5–8
    3, 3, 3, 3,        // 9–12
    4, 4, 4, 4,        // 13–16
    5, 5, 5, 5,        // 17–20
    6, 6, 6, 6,        // 21–24
    7, 7, 7, 7,        // 25–28
    8, 8, 8, 8,        // 29–32
    9, 9, 9, 9,        // 33–36
    10,10,10,10,       // 37–40
    11,11,11,11,       // 41–44
    12,12,12,12,       // 45–48
    13,13,13,13,       // 49–52
    14,14,14,14,       // 53–56
    15,15,15,15,       // 57–60
    16,16,16,16        // 61–64
};

constexpr std::uint8_t baseShift(std::uint8_t baseVal) {
    switch (baseVal) {
        case 2:  return 1;
        case 8:  return 3;
        case 16: return 4;
        default:  return 0; // or unreachable
    }
}

constexpr std::uint64_t UINT64_MAX_DIV10 = UINT64_MAX / 10;
constexpr std::uint8_t UINT64_MAX_LSD = UINT64_MAX % 10;

std::uint64_t convertFromBase(const std::string& inputNum, const Base base) {
    std::uint8_t baseVal = std::to_underlying(base);

    std::uint64_t decimalNumber = 0;
    std::uint8_t digit;

    if (base == Base::DEC) {
        for (char c : inputNum) {
            if ( decimalNumber > UINT64_MAX_DIV10 || ( decimalNumber == UINT64_MAX_DIV10 && (c - NUM_OFFSET) >= UINT64_MAX_LSD )) {
                return UINT64_MAX;
            }

            decimalNumber *= 10;
            decimalNumber += (c - NUM_OFFSET);
        }
    } else {
        for (char c : inputNum) {
            if (c >= DEC_MIN && c <= DEC_MAX) {
                digit = c - NUM_OFFSET;
            } else if (c >= HEX_MIN_UPPER && c <= HEX_MAX_UPPER) {
                digit = c - HEX_OFFSET_UPPER;
            } else {
                digit = c - HEX_OFFSET_LOWER;
            }

            // baseVal is only ever 2, 8 or 16 here
            if (decimalNumber >= (UINT64_MAX - digit) >> baseShift(baseVal) ) return UINT64_MAX;

            decimalNumber <<= baseShift(baseVal);
            decimalNumber += digit;
        }
    }

    return decimalNumber;
};

std::string convertToBase(std::uint64_t decimalNumber, const Base base) {
    if (decimalNumber == 0) return "0";

    if (base == Base::DEC) return std::to_string(decimalNumber);

    std::string nonDecimalNumberStr;
    std::uint8_t baseVal = std::to_underlying(base);
    std::uint8_t bitWidth = std::bit_width(decimalNumber);
    std::uint8_t predictedSize;

    switch (base) {
        case Base::OCT:
            predictedSize = bitWidthToOctWidth[bitWidth];
            break;

        case Base::HEX:
            predictedSize = bitWidthToHexWidth[bitWidth];
            break;

        default:
            predictedSize = bitWidth;
            break;
    }

    nonDecimalNumberStr.resize(predictedSize);
    for (std::int8_t i = predictedSize - 1; i>= 0; i--) {
        std::uint8_t remainder = decimalNumber % baseVal;

        if (remainder <= 9) {
            nonDecimalNumberStr[i] = static_cast<char>(remainder + NUM_OFFSET);
        } else {
            nonDecimalNumberStr[i] = static_cast<char>(remainder + HEX_OFFSET_UPPER);
        }

        decimalNumber /= baseVal;
    }

    return nonDecimalNumberStr;
};
