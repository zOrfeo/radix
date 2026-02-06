#ifndef PARSING_H
#define PARSING_H

#include <string>
#include "format.h"

format parseOptarg(const std::string& typeString);
format detectType(const std::string& inputNum);

#endif
