#if !defined(WORD_HPP)
#define WORD_HPP

#include <cstdint>

#include "util.hpp"
#include "tryte.hpp"

namespace termite
{
    // 12-trit balanced ternary integer type implemented using a binary-coded ternary (BCT) data representation
    // A total of 531441 states (-265720 through 265720)
    class Word {
    public:
        // The word with a value of -1
        static const Word MINUS_ONE;
    
        // The word with a value of 0
        static const Word ZERO;

        // The word with a value of 1
        static const Word ONE;

        // The BCT encoding of the word
        uint32_t bct;

        /////////////////////////////////////////
        // Constructors
        
        // Creates a word from it's BCT encoding
        Word(FromBCT, uint32_t bct);

        // Creates a word from a native integer
        Word(FromVal, int32_t val);
        
        // Creates a word from it's high and low trytes
        Word(const Tryte &hi, const Tryte &lo);

        /////////////////////////////////////////
        // Operators

        // 3's complement negation
        Word operator-() const;
        
        // Add operator
        Word operator+(const Word& other) const;

        // Subtract operator
        Word operator-(const Word& other) const;

        // Multiply operator
        Word operator*(const Word& other) const;

        // Divide operator
        Word operator/(const Word& other) const;

        // Tritwise NOT
        Word operator~() const;

        // Tritwise AND
        Word operator&(const Word& other) const;

        // Tritwise OR
        Word operator|(const Word& other) const;

        // Tritwise XOR
        Word operator^(const Word& other) const;

        /////////////////////////////////////////
        // Conversion
                
        // Converts a word into a native integer
        int32_t to_int32_t() const;

        // Converts a word into a ternary string
        std::string to_ternary_str() const;

        // Converts a word into a heptavigesimal string
        std::string to_hept_str() const;

        /////////////////////////////////////////
        // Misc

        // Checks if a word is negative
        bool is_neg() const;

        // Returns the high tryte of the word
        Tryte hi_tryte() const;

        // Returns the low tryte of the word
        Tryte lo_tryte() const;
    }   
} // namespace termite


#endif // WORD_HPP
