#if !defined(TRYBBLE_HPP)
#define TRYBBLE_HPP

#include <cstdint>
#include <string>
#include <array>

#include "util.hpp"

namespace termite {
    // 3-trit balanced ternary integer type implemented using a binary-coded ternary or BCT data representation
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

        // Creates a trybble from it's BCT encoding
        Trybble(FromBCT, uint8_t bct);

        // Creates a trybble from a native integer
        Trybble(FromVal, int8_t val);

        // Creates a trybble from it's constituent trits
        Trybble(FromTrits, const std::array<uint8_t, 3> &trits);

        // 3's complement negation
        Trybble operator-() const;
        
        // Add operator
        Trybble operator+(const Trybble& other) const;

        // Subtract operator
        Trybble operator-(const Trybble& other) const;

        // Multiply operator
        Trybble operator*(const Trybble& other) const;

        // Unsigned multiply operator
        Trybble umul(const Trybble& other) const;

        // Divide operator
        Trybble operator/(const Trybble& other) const;

        // Unsigned divide operator
        Trybble udiv(const Trybble& other) const;

        // Tritwise NOT
        Trybble operator~() const;

        // Tritwise AND
        Trybble operator&(const Trybble& other) const;

        // Tritwise OR
        Trybble operator|(const Trybble& other) const;

        // Checks if trybble is negative
        bool is_neg() const;

        // Converts a trybble into a trit array
        std::array<uint8_t, 3> get_trits() const;

        // Converts a trybble into a native signed integer
        int8_t to_int8_t() const;

        // Converts a trybble into a ternary string
        std::string to_ternary_str() const;

        // Converts a trybble into a septemvigesimal digit
        char to_sept_digit() const;
    };
} // namespace termite

#endif // TRYBBLE_HPP