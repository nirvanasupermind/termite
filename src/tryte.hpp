// -*- tryte.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef TRYTE_HPP
#define TRYTE_HPP

#include <string>
#include <cinttypes>

#include "trybble.hpp"

namespace termite {
    // 6-trit integer which represents values that range from -364 to 364 (3's complement signed) or 0 to 728 (int)
    class Tryte {
    private:
        Trybble hi;
        Trybble lo;
    public:
        // A tryte with a value of 0
        static const Tryte ZERO;

        // A tryte with a value of 1
        static const Tryte ONE;

        // A tryte with a value of 2
        static const Tryte TWO;

        // Default constructor
        Tryte() = default;

        // Converts two trybbles to a tryte
        Tryte(const Trybble& hi, const Trybble& lo);

        // Converts a native integer to a trybble
        Tryte(NativeInt, int num);

        // Converts a septemvigesimal (base 27) string to a tryte
        Tryte(Sept, const std::string& str); 

        // Tritwise AND
        Tryte operator&(const Tryte& other) const;

        // Tritwise OR
        Tryte operator|(const Tryte& other) const;

        // Tritwise XOR
        Tryte operator^(const Tryte& other) const;

        // Tritwise NOT
        Tryte operator~() const;

        // Gets high trybble (3 trits) from a tryte
        Trybble get_hi() const;

        // Gets low trybble (3 trits) from a tryte
        Trybble get_lo() const;

        // Converts a tryte to a native integer
        operator int() const;

        // Converts a tryte to a septemvigesimal (base 27) string
        operator std::string() const;
    };
} // namespace termite

#endif // TRYTE_HPP