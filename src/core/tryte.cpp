// -*- core/tryte.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "trybble.h"
#include "tryte.h"

namespace termite
{
    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : hi(hi), lo(lo)
    {
    }

    int8_t Tryte::hi_val() const
    {
        return hi.to_int8();
    }

    int8_t Tryte::lo_val() const
    {
        return lo.to_int8();
    }

    Tryte Tryte::operator+(const Tryte &other) const
    {
        return Tryte((uint8_t)0, (uint8_t)0);
    //    uint16_t a = bits();
    //    uint16_t b = other.bits();

    //    // Method based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html

    //    uint16_t t1 = a + 0b010101010101;
    //    uint16_t t2 = t1 + b;
    //    uint16_t t3 = t1 ^ b;
    //    uint16_t t4 = t2 ^ t3;
    //    uint16_t t5 = -t4 & // (not ieodso)


    //    return Tryte((uint8_t)(result >> 12), (uint8_t)(result - ((result >> 12) << 12)));
    }

    uint16_t Tryte::bits() const 
    {
        return (hi.bits >> 6) + lo.bits;
    }
} // namespace termite