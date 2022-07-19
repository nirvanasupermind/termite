#ifndef WORD_H
#define WORD_H

#include <string>

#include "../core/tryte.h"

namespace termite
{
    // Represents a memory address. 12 trits, with a total of 531441 states (-265720 through 265720).
    class Word
    {
    public:
        Tryte hi;

        Tryte lo;
        
        // Creates a word from it's constituent 2 trytes
        Word(const Tryte &hi, const Tryte &lo);


        // Checks if two words are equal
        bool operator==(const Word &other) const;

        // Returns a string representation of the word for printing/debugging
        std::string to_str() const;

        class HashFunction
        {
        public:
            size_t operator()(const Word &word) const;
        };
    };
} // namespace termite

#endif