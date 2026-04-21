#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include "base.h"
#include <cstdint>

std::uint64_t convertFromBase(const std::string& inputNum, const Base base);
std::string convertToBase(const std::uint64_t decimalNumber, const Base base);

#endif
