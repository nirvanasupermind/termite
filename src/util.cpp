#include <string>
#include <vector>
#include <iostream>

#include "util.h"

namespace termite
{
    std::string trim(std::string &str)
    {
        str.erase(str.find_last_not_of(' ') + 1); // suffixing spaces
        str.erase(0, str.find_first_not_of(' ')); // prefixing spaces
        return str;
    }

    std::vector<std::string> splitString(const std::string &s, char delim)
    {
        std::vector<std::string> v;
        std::string temp = "";
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == delim)
            {
                if (i == 0)
                {
                    temp += delim;
                }

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

    std::string joinVec(const std::vector<std::string> &v, char delim)
    {
        std::string s;

        for (int i = 0; i < v.size(); i++)
        {      
            if(v.at(i).front() == delim)
            {
                s += delim;
            }
            else
            {
                s += v.at(i);
                if(i != v.size() - 1)
                {
                    s += delim;
                }
            }
        }

        return s;
    }
}