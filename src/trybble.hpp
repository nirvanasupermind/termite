#if !defined(TRYBBLE_HPP)
#define TRYBBLE_HPP

#include <cstdint>
#include <string>

#include "util.hpp"

namespace termite {
    // 3-trit ternary integer type implemented using a binary-coded ternary or BCT data representation
    class Trybble {
    public:
        uint8_t bct;

        // Creates a trybble from it's BCT encoding
        Trybble(FromBCT, uint8_t bct);

        // Creates a trybble from a native integer
        Trybble(FromVal, uint8_t val);

        // 3's complement negation
        Trybble operator-() const;
        
        // Add operator
        Trybble operator+(const Trybble& other) const;

        // Subtract operator
        Trybble operator-(const Trybble& other) const;

        // Multiply operator
        Trybble operator*(const Trybble& other) const;

        // Converts a trybble to a native integer
        uint8_t to_uint8_t() const;

        // Converts a trybble to a ternary string
        std::string to_ternary_str() const;
    };
} // namespace termite

#endif // TRYBBLE_HPP