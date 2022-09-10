#if !defined(TRYBBLE_HPP)
#define TRYBBLE_HPP

#include <cstdint>
#include <string>
#include <array>

#include "util.hpp"

namespace termite {
    // 3-trit balanced ternary integer type implemented using a binary-coded ternary (BCT) data representation
    // A total of 27 states (-13 through 13)
    class Trybble {
    public:
        // The trybble with a value of -1
        static const Trybble MINUS_ONE;
    
        // The trybble with a value of 0
        static const Trybble ZERO;

        // The trybble with a value of 1
        static const Trybble ONE;

        // The BCT encoding of the trybble
        uint8_t bct;

        /////////////////////////////////////////
        // Constructors
        
        // Creates a trybble from it's BCT encoding
        Trybble(FromBCT, uint8_t bct);

        // Creates a trybble from a native integer
        Trybble(FromVal, int8_t val);

        /////////////////////////////////////////
        // Constructors
        
        // 3's complement negation
        Trybble operator-() const;
        
        // Add operator
        Trybble operator+(const Trybble& other) const;

        // Subtract operator
        Trybble operator-(const Trybble& other) const;

        // Multiply operator
        Trybble operator*(const Trybble& other) const;

        // Divide operator
        Trybble operator/(const Trybble& other) const;

        // Tritwise NOT
        Trybble operator~() const;

        // Tritwise AND
        Trybble operator&(const Trybble& other) const;

        // Tritwise OR
        Trybble operator|(const Trybble& other) const;

        // Tritwise XOR
        Trybble operator^(const Trybble& other) const;

        /////////////////////////////////////////
        // Conversion
        
        // Converts a trybble into a native integer
        int8_t to_int8_t() const;

        // Converts a trybble into a ternary string
        std::string to_ternary_str() const;

        // Converts a trybble into a heptavigesimal digit
        char to_hept_digit() const;

        /////////////////////////////////////////
        // Misc

        // Checks if a trybble is negative
        bool is_neg() const;
    };
} // namespace termite

#endif // TRYBBLE_HPP