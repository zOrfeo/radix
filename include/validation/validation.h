#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include "base.h"

bool validateBinary(const std::string& inputNum);
bool validateOctal(const std::string& inputNum);
bool validateDecimal(const std::string& inputNum);
bool validateHexadecimal(const std::string& inputNum);
bool validateInput(const std::string& inputNum, Base base);

#endif
