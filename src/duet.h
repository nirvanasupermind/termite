#ifndef DUET_H
#define DUET_H

#include "trit.h"

namespace termite
{
    // 2 trits, a total of 9 states (-4 through 4). Used for nonary strings.
    class Duet
    {
    public:
        Trit hi;

        Trit lo;

        // Creates a duet equal to 0
        Duet();

        // Creates a duet it's constiuent trits
        Duet(const Trit &hi, const Trit &lo);

        // Creates a duet from a character
        Duet(char chr);

        // Returns a clone of the duet
        Duet clone() const;

        // Returns a native integer representation of the duet
        int to_int() const;

        // Returns a character representation of the duet for printing/debugging
        char to_chr() const;
    };
} // namespace termite

#endif