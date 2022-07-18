#ifndef WORD_H
#define WORD_H

#include <string>
#include <array>

#include "tryte.h"

namespace termite
{
    // 12 trits, with a total of 531441 states (-265720 through 265720).
    class Word
    {
    public:
        Tryte hi;

        Tryte lo;
        
        // Creates a word from it's constituent 2 trytes
        Word(const Tryte &hi, const Tryte &lo);

        // // Creates a tryte from the 12 trits contained in it's constiuent trytes
        // Word(const std::array<Trit, 12> &trits);

        // Returns a string representation of the word for printing/debugging
        std::string to_str() const;
    };
} // namespace termite

#endif