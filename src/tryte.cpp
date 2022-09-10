#include <cstdint>
#include <string>
#include <exception>
#include <algorithm>

#include "util.hpp"
#include "trybble.hpp"
#include "tryte.hpp"

namespace termite
{
    const Tryte Tryte::MINUS_ONE(from_bct, 0b00'00'00'00'00'00);
    const Tryte Tryte::ZERO(from_bct, 0b00'00'00'00'00'01);
    const Tryte Tryte::ONE(from_bct, 0b00'00'00'00'00'10);

    Tryte::Tryte(FromBCT, uint16_t bct)
        : bct(bct) {
    }

    Tryte::Tryte(FromVal, int16_t val)
        : Tryte(Trybble(from_val, baldiv(val, 27)), Trybble(from_val, balmod(val, 27))) {
    }

    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : bct(hi.bct << 6 + lo.bct) {
    }

    Tryte Tryte::operator-() const {
        return operator~();
    }

    Tryte Tryte::operator+(const Trybble& other) const {
        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html

        uint16_t a = bct;
        uint16_t b = other.bct;

        uint16_t t1 = a + 0b01'01'01'01'01'01;
        uint16_t t2 = t1 + b;
        uint16_t t3 = t1 ^ b;
        uint16_t t4 = t2 ^ t3;
        uint16_t t5 = ~t4 & 0b10'10'10'10'10'100;
        uint16_t t6 = (t5 >> 2);
        uint16_t t7 = 0b10'10'10'10'10'10 - (t2 - t6);

        return Tryte(from_bct, t7);
    }
} // namespace termite