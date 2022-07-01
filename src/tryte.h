#ifndef TRYTE_H
#define TRYTE_H

#include <array>

#include "trit.h"
#include "trybble.h"

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

        // Creates a tryte from a native integer
        Tryte(int val);

        // Creates a tryte from it's constituent 6 trits
        Tryte(const std::array<Trit, 6> &trits);

        // Returns a clone of the tryte
        Tryte clone() const;

        // Returns the negation of the tryte
        Tryte operator-() const;

        // Returns the sum of two trytes
        Tryte operator+(const Tryte &other) const;

        // Returns the difference of two trytes
        Tryte operator-(const Tryte &other) const;
 
         // Returns the product of two trytes
        Tryte operator*(const Tryte &other) const;
 
        // Returns the tryte shifted to the left
        Tryte operator<<(int amount) const;

        // Returns the tryte shifted to the left
        Tryte operator>>(int amount) const;

        // Returns 1 if the first tryte is greater, -1 if the second tryte is greater, and 0 otherwise
        Trit cmp(const Tryte &other) const;

        // Checks if the two trytes are not equal
        bool operator!=(const Tryte &other) const;

        // Returns the hi trybble of the tryte
        Trybble hi_trybble() const;

        // Returns the lo trybble of the tryte
        Trybble lo_trybble() const;

        // Returns a native integer representation of the tryte
        int to_int() const;
        
        // Returns a longer, balanced ternary string of the tryte for printing/debugging
        std::string to_tern() const;

        // Returns a shorter, balanced heptavigesimal string of the tryte for printing/debugging
        std::string to_hept() const;

        // A tryte with a value of 0
        static const Tryte ZERO;
    };
} // namespace termite

#endif