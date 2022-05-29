#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace termite
{
    std::vector<std::string> splitString(const std::string &s, char delim);
}

#endif