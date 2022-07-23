//-*- core/trybble.h -*-/
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TRYBBLE_H
#define TRYBBLE_H

#include <cstdint>

namespace termite
{
    // A trybble is a ternary analog to a nybble, representing 3 trits or half a tryte of data.
    // We store trybbles in binary-coded ternary format where each trit is stored as 2 bits, 00 for 0, 01 for 1, and 10 for T.
    // For example, the bits 0b00_01_10 correspond to the trits 01T in balanced ternary.
    // Trybbles corresponds to a heptavigesimal (base-27) digits, like how nybbles correspond to hex digits.

    typedef uint8_t Trybble;
    
} // namespace termite

#endif // TRYBBLE_H