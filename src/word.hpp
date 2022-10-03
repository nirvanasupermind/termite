// -*- word.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef WORD_HPP
#define WORD_HPP

#include <string>
#include <cinttypes>

#include "typedefs.hpp"
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

        // Converts two trytes to a word
        Word(const Tryte& hi, const Tryte& lo);

        // Converts a native signed integer to a word
        static Word from_i32(i32 num);

        // Converts a native unsigned integer to a word
        static Word from_u32(u32 num);

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

        // Unsigned modulo
        Word umod(const Word& other) const;

        // Negate
        Word operator-() const;

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

        // Converts a word to a native signed integer
        i32 to_i32() const;

        // Converts a word to a native unsigned integer
        u32 to_u32() const;
        
        // Converts a word to a ternary string
        std::string to_ternary_str() const;

        // Converts a word to a septemvigesimal (base 27) string, a compact representation of ternary
        std::string to_sept_str() const;
    };
} // namespace termite

#endif // WORD_HPP