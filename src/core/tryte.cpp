// -*- core/tryte.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "util.h"
#include "trybble.h"
#include "tryte.h"

namespace termite {
    Tryte::Tryte(const Trybble& hi, const Trybble& lo)
        : hi(hi), lo(lo) {
        // assert(valid());
    }

    Tryte::Tryte(FromBits, uint16_t bits)
        : hi(Trybble(from_bits, bits >> 6)), lo(Trybble(from_bits, bits & 63)) {
        // assert(valid());
    }


    Tryte::Tryte(uint16_t val)
        : hi(Trybble(val / 27)), lo(Trybble(val % 27)) {
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

    int8_t Tryte::hi_val() const {
        return hi.to_int8();
    }

    int8_t Tryte::lo_val() const {
        return lo.to_int8();
    }

    uint16_t Tryte::bits() const {
        return (hi.bits << 6) + lo.bits;
    }

    bool Tryte::is_neg() const {
        return bits() > 0b010101010101;
    }

    int16_t Tryte::to_int16() const {
        if(is_neg()) {
            return 364 - to_uint16();
        } else {
            return to_uint16();
        }
    }

    uint16_t Tryte::to_uint16() const {
        return hi.to_uint8() * 27 + lo.to_uint8();
    }

    std::string Tryte::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    Tryte Tryte::operator+(const Tryte& other) const {
        uint16_t a = bits();
        uint16_t b = other.bits();

        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html
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

    Tryte Tryte::operator-() const {
        return operator~() + Tryte::ONE;
    }

    Tryte Tryte::operator-(const Tryte& other) const {
        return operator+(-other);
    }

    Tryte Tryte::operator*(const Tryte& other) const {
        if (is_neg() && other.is_neg()) {
            return operator-().mulu(-other);
        } else if(is_neg()) {
            return -(operator-().mulu(other));
        } else if(other.is_neg()) {
            return -mulu(-other);
        } else {
            return mulu(other);
        }
    }

    Tryte Tryte::mulu(const Tryte& other) const {
        // Yet to find an algorithm for BCT (or even BCD) multiplication/division
        // so for now the multiplication and division functions are implemented
        // by converting to a native integer and back

        uint16_t a = to_uint16();
        uint16_t b = other.to_uint16();
        uint16_t c = a * b;

        return Tryte(c / 27, c % 27);
    }

    Tryte Tryte::operator/(const Tryte& other) const {
        if (is_neg() && other.is_neg()) {
            return operator-().divu(-other);
        } else if(is_neg()) {
            return -(operator-().divu(other));
        } else if(other.is_neg()) {
            return -divu(-other);
        } else {
            return divu(other);
        }
    }

    Tryte Tryte::divu(const Tryte& other) const {
        int16_t a = to_int16();
        int16_t b = other.to_int16();
        int16_t c = a / b;

        return Tryte(c);
    }

    Tryte Tryte::operator~() const {
        uint16_t result_bits = 0b101010101010 - bits();
        return Tryte(from_bits, result_bits);
    }

    const Tryte Tryte::ONE(0, 1);
} // namespace termite