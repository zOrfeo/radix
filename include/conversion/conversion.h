#ifndef CONVERSION_H
#define CONVERSION_H

#include <string>
#include "base.h"

int convertFromBase(const std::string& inputNum, const Base base);
std::string convertToBase(const int decimalNumber, const Base base);

#endif
