#ifndef TRYBBLE_H
#define TRYBBLE_H

#include "trit.h"

namespace termite
{
    // 3 trits, a total of 27 states (-13 through 13).
    class Trybble
    {
    public:
        Trit trit0;

        Trit trit1;

        Trit trit2;

        // Creates a duet equal to 0
        Trybble();

        // Creates a trybble it's constiuent trits
        Trybble(const Trit &trit0, const Trit &trit1, const Trit &trit2);

        // Creates a trybble from a character
        Trybble(char chr);

        // Returns a clone of the trybble
        Trybble clone() const;

        // Returns a native integer representation of the trybble
        int to_int() const;

        // Returns a character representation of the trybble for printing/debugging
        char to_chr() const;
    };
} // namespace termite

#endif