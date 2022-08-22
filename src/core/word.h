// -*- core/word.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef WORD_H
#define WORD_H

#include <string>
#include <cstdint>

#include "util.h"
#include "halfword.h"

namespace termite {
    // A word is the natural unit of data used by the VM, representing 24 trits or 4 trytes of data.
    // Most often, words are used as a numerical data type, with their trits 
    // encoding the ternary representation of a number from -141214768240 to +141214768240.
    
    class Word {
    public:
        Halfword hi;

        Halfword lo;

        // Creates a BCT word equal to 0.
        Word() = default;

        // Convert two BCT halfwords to a BCT word.
        Word(const Halfword& hi, const Halfword& lo);

        // Converts raw bits to a BCT word.
        Word(FromBits, uint64_t bits);

        // Converts a native uint64 to a BCT word.
        Word(uint64_t val);

        // Returns the value of the BCT word's high halfword.
        int32_t hi_val() const;

        // Returns the value of the BCT word's low halfword.
        int32_t lo_val() const;

        // Returns the internal bits of the BCT word, stored inside a native uint64.
        uint64_t bits() const;

        // Converts the BCT word to a native int64.
        int64_t to_int64() const;

        // Converts the BCT word to a native uint64.
        uint64_t to_uint64() const;

        // Returns true if the BCT word has a negative value when using 3's complement, and false otherwise.
        bool is_neg() const;

        // Converts the BCT word to a ternary string.
        std::string to_ternary_str() const;

        // Returns the sum of two BCT words.
        Word operator+(const Word& other) const;

        // Returns the negation (3's complement) of the BCT word.
        Word operator-() const;

        // Returns the difference of two BCT words.
        Word operator-(const Word& other) const;

        // Returns the product of two BCT words.
        Word operator*(const Word& other) const;

        // Returns the unsigned product of two BCT words.
        Word mulu(const Word& other) const;

        // Returns the quotient of two BCT words.
        Word operator/(const Word& other) const;

        // Returns the unsigned quotient of two BCT words.
        Word divu(const Word& other) const;

        // Returns the tritwise NOT of the BCT word.
        Word operator~() const;

        static const Word ONE;
    };
} // namespace termite

#endif // HALFWORD_H