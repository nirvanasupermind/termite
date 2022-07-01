#ifndef TRYBBLE_H
#define TRYBBLE_H

#include <array>

#include "trit.h"

namespace termite
{
    // Ternary analogue to a nybble. 3 trits or half of a tryte.
    class Trybble
    {
    public:
        std::array<Trit, 3> trits;

        // Creates a trybble equal to 0
        Trybble() = default;

        // Creates a tryte from it's constituent 3 trits
        Trybble(const std::array<Trit, 3> &trits);
        
        // Returns a clone of the trybble
        Trybble clone() const;

        // Returns a native integer representation of the trybble
        int to_int() const;

        // Returns a balanced heptavigesimal character representation of the trybble for printing/debugging
        char to_chr() const;

        // A trybble with a value of 0
        static const Trybble ZERO;
    };
} // namespace termite

#endif