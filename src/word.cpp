#include <string>

#include "tryte.h"
#include "word.h"

namespace termite
{
    Word::Word(const Tryte &hi, const Tryte &mid, const Tryte &lo)
        : hi(hi), mid(mid), lo(lo)
    {
    }

    std::string Word::to_str() const
    {
        return hi.to_str() + mid.to_str() + lo.to_str();
    }
} // namespace termite
