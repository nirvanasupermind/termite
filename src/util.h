#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace termite
{
    std::string trim(std::string &str);

    std::vector<std::string> splitString(const std::string &s, char delim);

    std::string joinVec(const std::vector<std::string> &v, char delim);
}

#endif