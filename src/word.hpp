// -*- word.hpp -*-
// Part of the Termite project, under the MIT License.

#if !defined(WORD_HPP)
#define WORD_HPP

#include <string>
#include <cinttypes>

#include "tryte.hpp"

namespace termite
{
    // 12-trit balanced ternary integer type with values from -265720 through 265720
    // Implemented using binary-coded ternary (BCT) representation, where each trit is encoded by 2 bits

    class Word {
    public:
        // Default constructor
        Word();

        // Creates a tryte from it's high and low trybbles
        Word(const Tryte& hi, const Tryte& lo);

        // Creates a tryte from a native integer
        Word(int32_t num);

        // Returns the sum of two words
        Word operator+(const Word& other) const;

        // Returns the difference of two words
        Word operator-(const Word& other) const;

        // Returns the product of two words
        Word operator*(const Word& other) const;

        // Returns the quotient of two words
        Word operator/(const Word& other) const;

        // Returns the tritwise NOT of a word
        Word operator~() const;

        // Returns the tritwise AND of two words
        Word operator&(const Word& other) const;

        // Returns the tritwise OR of two words
        Word operator|(const Word& other) const;

        // Returns the high tryte of a word
        Tryte get_hi() const;

        // Returns the low tryte of a word
        Tryte get_lo() const;

        // Returns a native integer representation of a word
        int16_t to_int() const;

        // Returns a ternary string representation of a word
        std::string to_ternary_str() const;

        // Returns a septemvigesimal (base 27) string representation of a word
        std::string to_sept_str() const;

        // Returns a Termite Character Set character corresponding to a word
        std::string to_tcs_char() const;
    protected:
        Tryte hi;

        Tryte lo;
    };
} // namespace termite


#endif // WORD_H