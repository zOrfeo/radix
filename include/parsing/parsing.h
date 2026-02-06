#ifndef PARSING_H
#define PARSING_H

#include <string>
#include "numericFMT.h"

numericFMT parseTypeOption(const std::string& typeString);
numericFMT detectType(const std::string& inputNum);

#endif
