// -*- core/tryte.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

#include "util.h"
#include "trybble.h"
#include "tryte.h"

namespace termite
{
    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : hi(hi), lo(lo)
    {
        // assert(valid());
    }

    Tryte::Tryte(FromBits, uint16_t bits)
        : hi(Trybble(from_bits, bits >> 6)), lo(Trybble(from_bits, bits & 63))
    {
        // assert(valid());
    }

    // bool Tryte::valid() const 
    // {
    //     uint16_t a = bits();
    //     uint16_t t1 = a & 0b010101010101;
    //     uint16_t t2 = a ^ 0b010101010101;
    //     uint16_t t3 = t1 ^ t2;
    //     uint16_t t4 = t3 & 0b101010101010;
    //     return (t4 & 4095) == 0;
    // }

    int8_t Tryte::hi_val() const
    {
        return hi.to_int8();
    }

    int8_t Tryte::lo_val() const
    {
        return lo.to_int8();
    }
    
    uint16_t Tryte::bits() const 
    {
        return (hi.bits >> 6) + lo.bits;
    }
 
    Tryte Tryte::operator+(const Tryte &other) const
    {
       uint16_t a = bits();
       uint16_t b = other.bits();

       // Method based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html

       uint16_t t1 = a + 0b010101010101;
       uint16_t t2 = t1 + b;
       uint16_t t3 = t1 ^ b;
       uint16_t t4 = t2 ^ t3;
       uint16_t t5 = ~t4 & 0b1010101010100;
       uint16_t t6 = (t5 >> 2); 
       uint16_t t7 = t2 - t6;

    //    std::cout << t7 << '\n';
       return Tryte(from_bits, t7);
    }

    Tryte Tryte::operator-() const
    {
        return operator~() + Tryte::ONE;
    }

    Tryte Tryte::operator-(const Tryte &other) const
    {
        return operator+(-other);
    }

    Tryte Tryte::operator~() const
    {
        uint16_t result_bits = 0b101010101010 - bits();
        return Tryte(from_bits, result_bits);
    }

    std::string Tryte::to_ternary_str() const
    {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    const Tryte Tryte::ONE(0, 1);
} // namespace termite