#ifndef WORD_H
#define WORD_H

#include <string>

#include "tryte.h"

namespace termite
{
    // Represents a pair of trytes. 12 trits, with a total of 531441 states (-265720 through 265720).
    class Word
    {
    public:
        Tryte hi;

        Tryte mid;

        Tryte lo;

        // Creates a word from it's constituent 2 trytes
        Word(const Tryte &hi, const Tryte &mid, const Tryte &lo);

        // Returns a string representation of the word for printing/debugging
        std::string to_str() const;
    };
} // namespace termite

#endif