#ifndef PARSING_H
#define PARSING_H

#include <string>
#include "base.h"

Base parseBase(const std::string& typeString);
BasePrefix detectPrefix(const std::string& inputNum);

#endif
