#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include "base.h"
#include <cstdint>

int convertFromBase(const std::string& inputNum, const Base base);
std::string convertToBase(const std::uint32_t decimalNumber, const Base base);
std::uint32_t stringToUInt32(const std::string& string);

#endif
