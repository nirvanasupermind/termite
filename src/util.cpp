#include <string>
#include <vector>

#include "util.h"

namespace termite
{
    std::vector<std::string> splitString(const std::string &s, char delim)
    {
        std::vector<std::string> v;
        std::string temp = "";
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == delim)
            {
                v.push_back(temp);
                temp = "";
            }
            else
            {
                temp.push_back(s.at(i));
            }
        }

        v.push_back(temp);

        return v;
    }
}