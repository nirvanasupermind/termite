// -*- core/tryte.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TRYTE_H
#define TRYTE_H

#include <string>
#include <cstdint>

#include "trybble.h"

namespace termite
{
    // A tryte is a ternary analog to a byte, representing 6 trits or 2 trybbles of data.
    // BCT trytes are frequently used as numerical data types.

    class Tryte
    {
    public:
        Trybble hi;

        Trybble lo;

        // Convert two BCT trybbles to a tryte.
        Tryte(const Trybble &hi, const Trybble &lo);

        // Returns a value of the BCT tryte's high trybble.
        int8_t hi_val() const;

        // Returns a value of the BCT tryte's low trybble.
        int8_t lo_val() const;

        // Returns the sum of two BCT trytes.
        Tryte operator+(const Tryte &other) const;

        // Returns the negation of the BCT BCT trytes.
        Tryte operator-() const;

        // Returns the difference of two BCT trytes.
        Tryte operator-(const Tryte &other) const;

        // Returns the product of two BCT trytes.
        Tryte operator*(const Tryte &other) const;

        // Returns the internal bits of the BCT tryte, stored inside a native uint16.
        uint16_t bits() const;

        // Converts the BCT tryte to a native int16.
        int16_t to_int16() const; 

        // Converts the BCT tryte to a ternary string.
        std::string to_ternary_str() const;
    };
} // namespace termite

#endif // TRYTE_H