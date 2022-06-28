#ifndef TRYTE_H
#define TRYTE_H

#include <array>

#include "trit.h"

namespace termite
{
    // Ternary analogue to a byte. 6 trits, a total of 729 states (-364 through 364).
    class Tryte
    {
    public:
        // The tryte's constituent 6 trits
        std::array<Trit, 6> trits;

        // Creates a tryte equal to 0
        Tryte() = default;

        // Creates a tryte from it's constituent 6 trits
        Tryte(const std::array<Trit, 6> &trits);

        // Returns the negation of a tryte
        Tryte operator-() const;

        // Returns the sum of two trytes
        Tryte operator+(const Tryte &other) const;

        // Returns the difference of two trytes
        Tryte operator-(const Tryte &other) const;
 
        // Returns a string representation of the tryte for printing/debugging
        std::string to_str() const;
    };
} // namespace termite

#endif