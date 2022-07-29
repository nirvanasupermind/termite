// -*- core/trybble.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TRYBBLE_H
#define TRYBBLE_H

#include <cstdint>
#include <array>

namespace termite
{
    // A trybble is a ternary analog to a nybble, representing 3 trits or half a tryte of data.
    // We store trybbles in binary-coded ternary format where each trit is stored as 2 bits, 00 for 0, 01 for 1, and 10 for T.
    // For example, the bits 0b00_01_10 correspond to the trits 01T in balanced ternary.

    class Trybble
    {
    public:
        uint8_t bits;

        Trybble();

        Trybble(uint8_t bits);

        // Converts a native int8 to a BCT trybble.
        Trybble(int8_t val);

        // Converts the BCT trybble to a native int8.
        int8_t to_int8() const;

        // Converts the BCT trybble to a ternary string.
        std::string to_ternary_str() const;
    
        // Converts the BCT trybble to a heptavigesimal character.
        char to_hept_chr() const;
    
        // // Returns the first BCT trit of the BCT trybble.
        // uint8_t first_trit() const;

        // // Returns the second BCT trit of the BCT trybble.
        // uint8_t second_trit() const;

        // // Returns the third BCT trit of the BCT trybble.
        // uint8_t third_trit() const;
    };
    
} // namespace termite

#endif // TRYBBLE_H