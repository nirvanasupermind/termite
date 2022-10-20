// -*- word.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef WORD_HPP
#define WORD_HPP

#include <string>
#include <cinttypes>

#include "tryte.hpp"

namespace termite {
    // 12-trit integer which represents values that range from -265720 to 265720 (3's complement signed)
    // or 0 to 531440 (unsigned)
    class Word {
    private:
        Tryte hi;
        Tryte lo;
    public:        
        // A word with a value of 0
        static const Word ZERO;

        // A word with a value of 1
        static const Word ONE;

        // A word with a value of 2
        static const Word TWO;

        // Default constructor
        Word() = default;
        
        // Converts two trytes to a word
        Word(const Tryte& hi, const Tryte& lo);

        // Converts a native integer to a word
        Word(NativeInt, unsigned int num);

        // Converts a septemvigesimal (base 27) string to a word
        Word(Sept, const std::string& str);

        // Add
        Word operator+(const Word& other) const;

        // Subtract
        Word operator-(const Word& other) const;

        // Multiply
        Word operator*(const Word& other) const;

        // Unsigned multiply
        Word umul(const Word& other) const;

        // Divide
        Word operator/(const Word& other) const;

        // Unsigned divide
        Word udiv(const Word& other) const;

        // Modulo
        Word operator%(const Word& other) const;

        // Increments a word, only used as a utility when writing test machine code programs
        Word operator++();

        // Tritwise AND
        Word operator&(const Word& other) const;

        // Tritwise OR
        Word operator|(const Word& other) const;

        // Tritwise XOR
        Word operator^(const Word& other) const;

        // Tritwise NOT
        Word operator~() const;
        
        // Gets high tryte (6 trits) from a word
        Tryte get_hi() const;

        // Gets low tryte (6 trits) from a word
        Tryte get_lo() const;

        // Converts a word to a native integer
        operator unsigned int() const;

        // Converts a word to a septemvigesimal (base 27) string
        operator std::string() const;
    };
} // namespace termite

#endif // WORD_HPP