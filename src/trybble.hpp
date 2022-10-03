// -*- trybble.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef TRYBBLE_HPP
#define TRYBBLE_HPP

#include <string>
#include <cinttypes>

#include "typedefs.hpp"

namespace termite
{
    // 3-trit integer which represents values that range from -13 to 13 (3's complement signed) or 0 to 26 (unsigned)
    class Trybble {
    private:
        u8 bct;
    public:        
        // A trybble with a value of 0
        static const Trybble ZERO;

        // A trybble with a value of 1
        static const Trybble ONE;

        // Default constructor
        Trybble();

        // Converts BCT data to a trybble
        Trybble(u8 bct);

        // Converts a native signed integer to a trybble
        static Trybble from_i8(i8 num);

        // Converts a native unsigned integer to a trybble
        static Trybble from_u8(u8 num);

        // Tritwise AND
        Trybble operator&(const Trybble &other) const;

        // Tritwise OR
        Trybble operator|(const Trybble &other) const;

        // Tritwise XOR
        Trybble operator^(const Trybble &other) const;

        // Tritwise NOT
        Trybble operator~() const;

        // Gets BCT data from a trybble
        u8 get_bct() const;
    
        // Converts a trybble to a native signed integer
        i8 to_i8() const;
    
        // Converts a trybble to a native unsigned integer
        u8 to_u8() const;

        // Converts a trybble to a ternary string
        std::string to_ternary_str() const;

        // Converts a trybble to a septemvigesimal (base 27) character, compact representation of ternary
        char to_sept_char() const;
    }; 
} // namespace termite

#endif // TRYBBLE_HPP