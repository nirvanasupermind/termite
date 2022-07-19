#include <string>

#include "../core/tryte.h"
#include "word.h"

namespace termite
{
    Word::Word(const Tryte &hi, const Tryte &lo)
        : hi(hi), lo(lo)
    {
    }

    // Word::Word(const std::array<Trit, 12> &trits)
    //     : hi(Tryte(std::array<Trit, 6> {trits.begin(), trits.begin() + 5})), lo(Tryte(std::array<Trit, 6> {trits.begin() + 6, trits.end()}))
    // {
    // }

    bool Word::operator==(const Word &other) const
    {
        return hi.to_int() == other.hi.to_int() && lo.to_int() == other.lo.to_int();
    }

    std::string Word::to_str() const
    {
        return hi.to_str() + lo.to_str();
    }

    size_t Word::HashFunction::operator()(const Word &word) const
    {   
        return Tryte::HashFunction()(word.hi) ^ Tryte::HashFunction()(word.lo);
    }    
} // namespace termite
