#include <string>
#include <array>

#include "tryte.h"
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

    std::string Word::to_str() const
    {
        return hi.to_str() + lo.to_str();
    }
} // namespace termite
