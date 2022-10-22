// -*- trybble.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef TRYBBLE_HPP
#define TRYBBLE_HPP

#include <cinttypes>
#include <string>

#include "util.hpp"

namespace termite
{
    // 3-trit integer which represents values that range from -13 to 13 (3's complement signed) or 0 to 26 (int)
    class Trybble {
    private:
        uint8_t bct;
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
        Trybble(uint8_t bct);

        // Converts a native integer to a trybble
        Trybble(NativeInt, int num);

        // Converts a septemvigesimal (base 27) string to a trybble
        Trybble(Sept, const std::string& str);

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
        operator int() const;

        // Converts a trybble to a septemvigesimal (base 27) string
        operator std::string() const;
    }; 
} // namespace termite

#endif // TRYBBLE_HPP