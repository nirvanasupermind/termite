// -*- core/tryte.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TRYTE_H
#define TRYTE_H

#include <string>
#include <cstdint>

#include "util.h"
#include "trybble.h"

namespace termite {
    // A tryte is a ternary analog to a byte, representing 6 trits or 2 trybbles of data.
    // Most often, trytes are used as a numerical data type, with their trits 
    // encoding the ternary representation of a number from -364 to +364.
    
    class Tryte {
    public:
        Trybble hi;

        Trybble lo;

        // Creates a BCT tryte equal to 0.
        Tryte() = default;

        // Convert two BCT trybbles to a BCT tryte.
        Tryte(const Trybble& hi, const Trybble& lo);

        // Converts raw bits to a BCT tryte.
        Tryte(FromBits, uint16_t bits);

        // Convert a native uint16 to a BCT tryte.
        Tryte(uint16_t bits);

        // bool valid() const;

        // Returns a value of the BCT tryte's high trybble.
        int8_t hi_val() const;

        // Returns a value of the BCT tryte's low trybble.
        int8_t lo_val() const;

        // Returns the internal bits of the BCT tryte, stored inside a native uint16.
        uint16_t bits() const;

        // Returns true if the tryte has a negative value when using 3's complement, and false otherwise.
        bool is_neg() const;

        // Converts the BCT tryte to a native int16.
        int16_t to_int16() const;

        // Converts the BCT tryte to a native uint16.
        uint16_t to_uint16() const;

        // Converts the BCT tryte to a ternary string.
        std::string to_ternary_str() const;

        // Converts the BCT tryte to a heptavigesimal string.
        std::string to_hept_str() const;

        // Returns the sum of two BCT trytes.
        Tryte operator+(const Tryte& other) const;

        // Returns the negation (3's complement) of the BCT tryte.
        Tryte operator-() const;

        // Returns the difference of two BCT trytes.
        Tryte operator-(const Tryte& other) const;

        // Returns the product of two BCT trytes.
        Tryte operator*(const Tryte& other) const;

        // Returns the unsigned product of two BCT trytes.
        Tryte mulu(const Tryte& other) const;

        // Returns the quotient of two BCT trytes.
        Tryte operator/(const Tryte& other) const;

        // Returns the unsigned quotient of two BCT trytes.
        Tryte divu(const Tryte& other) const;

        // Returns the tritwise NOT of the BCT tryte.
        Tryte operator~() const;

        static const Tryte ONE;
    };
} // namespace termite

#endif // TRYTE_H