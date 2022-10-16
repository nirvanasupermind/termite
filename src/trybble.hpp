// -*- trybble.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef TRYBBLE_HPP
#define TRYBBLE_HPP

#include <string>

#include "util.hpp"

namespace termite
{
    // 3-trit integer which represents values that range from -13 to 13 (3's complement signed) or 0 to 26 (unsigned)
    class Trybble {
    private:
        char bct;
    public:        
        // A trybble with a value of 0
        static const Trybble ZERO;

        // A trybble with a value of 1
        static const Trybble ONE;

        // A trybble with a value of 2
        static const Trybble TWO;

        // Default constructor
        Trybble();

        // Converts BCT data to a trybble
        Trybble(char bct);

        // Converts a native integer to a trybble
        Trybble(NativeInt, int num);

        // Converts a septemvigesimal (base 27) digit to a trybble
        Trybble(Sept, char digit);

        // Tritwise AND
        Trybble operator&(const Trybble &other) const;

        // Tritwise OR
        Trybble operator|(const Trybble &other) const;

        // Tritwise XOR
        Trybble operator^(const Trybble &other) const;

        // Tritwise NOT
        Trybble operator~() const;

        // Gets BCT data from a trybble
        uint8_t get_bct() const;

        // Converts a trybble to a native integer
        operator unsigned int() const;

        // Converts a trybble to a septemvigesimal (base 27) digit
        operator char() const;
    }; 
} // namespace termite

#endif // TRYBBLE_HPP