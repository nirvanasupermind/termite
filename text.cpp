#include <string>
#include <vector>
#include <cwchar>

#include "text.h"
#include "trit.h"

namespace termite
{
    std::vector<Tryte> encodeString(const std::wstring &str)
    {
        std::vector<Tryte> result;

        for(int i = 0; i < str.size(); i++) 
        {
            result.push_back(encodeChar(str.at(i)));
        }

        return result;
    }

    Tryte encodeChar(wchar_t chr) 
    {
        return Tryte((int)chr);
    }

    std::wstring decodeString(const std::vector<Tryte> &str)
    {
        std::wstring result;

        for(int i = 0; i < str.size(); i++) 
        {
            result.push_back(decodeChar(str.at(i)));
        }

        return result;
    }

    wchar_t decodeChar(const Tryte &chr) 
    {
        return (wchar_t)(chr.intVal());
    }
}