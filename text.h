#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include <cwchar>

#include "tryte.h"

namespace termite
{
    // Wide strings and chars are used here so Unicode can be used properly.
    
    std::vector<Tryte> encodeString(const std::wstring &str);

    Tryte encodeChar(wchar_t chr);
    
    std::wstring decodeString(const std::vector<Tryte> &str);    

    wchar_t decodeChar(const Tryte &chr);
}

#endif