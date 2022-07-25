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
    // Trytes are frequently used as numerical data types.

    class Tryte
    {
    protected:
        Trybble hi;

        Trybble lo;

        static uint8_t add_bct_trits(uint8_t a, uint8_t b);
    public:
        // Convert two BCT trybbles to a tryte.
        Tryte(const Trybble &hi, const Trybble &lo);

        // Returns the BCT representation of the tryte's high trybble.
        Trybble hi_bct() const;

        // Returns the BCT representation of the tryte's low trybble.
        Trybble lo_bct() const;

        // Returns a value of the tryte's high trybble.
        int8_t hi_val() const;

        // Returns a value of the tryte's low trybble.
        int8_t lo_val() const;

        // Returns the sum of two trytes.
        Tryte operator+(const Tryte &other) const;

        // Returns the negation of the trytes.
        Tryte operator-() const;

        // Returns the difference of two trytes.
        Tryte operator-(const Tryte &other) const;

        // Returns the product of two trytes.
        Tryte operator*(const Tryte &other) const;

        // Converts the tryte to a native integer.
        int to_int() const;

        // Converts the tryte to a ternary string.
        std::string to_ternary_str() const;
    };
} // namespace termite

#endif // TRYTE_H