#ifndef CORE_H
#define CORE_H

#include <getopt.h>
#include <unistd.h>
#include <string>
#include "base.h"
#include <unistd.h>

std::pair<int, std::string> processInput(std::string& inputNum, Base inBase, Base outBase);
std::string buildPrefix(Base base);

#endif
