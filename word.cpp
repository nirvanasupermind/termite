#include <iostream>
#include <string>

#include "tryte.h"
#include "word.h"

namespace termite
{
    Word::Word(const Tryte &hi, const Tryte &lo)
        : hi(hi), lo(lo)
    {   
    }

    Word::Word(const std::string &str)
        : hi(Tryte(str.substr(0, 6)), Tryte(str.substr(6))
    {   
    }

    std::string Word::str() const
    {
        return hi.str() + lo.str();
    }
}