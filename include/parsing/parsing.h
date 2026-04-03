#ifndef PARSING_H
#define PARSING_H

#include <string>
#include "base.h"

Base parseBaseOption(const std::string& typeString);
BasePrefix detectPrefix(const std::string& inputNum);

#endif
