// -*- tryte.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef TRYTE_HPP
#define TRYTE_HPP

#include <string>
#include <cinttypes>

#include "typedefs.hpp"
#include "trybble.hpp"

namespace termite {
    // 6-trit integer which represents values that range from -364 to 364 (3's complement signed) or 0 to 728 (unsigned)
    class Tryte {
    private:
        Trybble hi;
        Trybble lo;
    public:
        // A tryte with a value of 0
        static const Tryte ZERO;

        // A tryte with a value of 1
        static const Tryte ONE;

        // Converts two trybbles to a tryte
        Tryte(const Trybble& hi, const Trybble& lo);

        // Converts a native signed integer to a trybble
        static Tryte from_i16(i16 num);

        // Converts a native unsigned integer to a trybble
        static Tryte from_u16(u16 num);

        // Add
        Tryte operator+(const Tryte& other) const;

        // Subtract
        Tryte operator-(const Tryte& other) const;

        // Multiply
        Tryte operator*(const Tryte& other) const;

        // Signed multiply
        Tryte smul(const Tryte& other) const;

        // Divide
        Tryte operator/(const Tryte& other) const;

        // Signed divide
        Tryte sdiv(const Tryte& other) const;

        // Modulo
        Tryte operator%(const Tryte& other) const;

        // Signed modulo
        Tryte smod(const Tryte& other) const;

        // Three's complement / negation
        Tryte operator-() const;

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

        // Converts a tryte to a native signed integer
        i16 to_i16() const;

        // Converts a tryte to a native unsigned integer
        u16 to_u16() const;

        // Converts a tryte to a ternary string
        std::string to_ternary_str() const;

        // Converts a tryte to a septemvigesimal (base 27) string, a compact representation of ternary
        std::string to_sept_str() const;
    };
} // namespace termite

#endif // TRYBBLE_HPP