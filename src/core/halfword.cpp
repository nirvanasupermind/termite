// -*- core/halfword.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "util.h"
#include "trybble.h"
#include "tryte.h"
#include "halfword.h"

namespace termite {
    Halfword::Halfword(const Tryte& hi, const Tryte& lo)
        : hi(hi), lo(lo) {

    }

    Halfword::Halfword(FromBits, uint32_t bits)
        : hi(Tryte(from_bits, bits >> 12)), lo(Tryte(from_bits, bits & 4095)) {
    }

    Halfword::Halfword(uint32_t bits)
        : hi(Tryte(bits / 729)), lo(Tryte(bits % 729)) {
    }

    int16_t Halfword::hi_val() const {
        return hi.to_int16();
    }

    int16_t Halfword::lo_val() const {
        return lo.to_int16();
    }

    uint32_t Halfword::bits() const {
        return (hi.bits() << 12) + lo.bits();
    }

    bool Tryte::is_neg() const {
        return bits() > 0b010101010101010101010101;
    }

    int32_t Halfword::to_int32() const {
        if (is_neg()) {
            return 265720 - to_uint32();
        } else {
            return to_uint32();
        }
    }

    uint32_t Halfword::to_uint32() const {
        return hi.to_uint16() * 729 + lo.to_uint16();
    }

    std::string Halfword::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    std::string Halfword::to_hept_str() const {
        return hi.to_hept_str() + lo.to_hept_str();
    }

    Halfword Halfword::operator+(const Halfword& other) const {
        uint32_t a = bits();
        uint32_t b = other.bits();

        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html
        uint32_t t1 = a + 0b010101010101010101010101;
        uint32_t t2 = t1 + b;
        uint32_t t3 = t1 ^ b;
        uint32_t t4 = t2 ^ t3;
        uint32_t t5 = ~t4 & 0b1010101010101010101010100;
        uint32_t t6 = (t5 >> 2);
        uint32_t t7 = t2 - t6;

        //    std::cout << t7 << '\n';
        return Halfword(from_bits, t7);
    }

    Halfword Halfword::operator-() const {
        return operator~() + Halfword::ONE;
    }

    Halfword Halfword::operator-(const Halfword& other) const {
        return operator+(-other);
    }

    Halfword Halfword::operator*(const Halfword& other) const {
        if (is_neg() && other.is_neg()) {
            return operator-().mulu(-other);
        }
        else if (is_neg()) {
            return -(operator-().mulu(other));
        }
        else if (other.is_neg()) {
            return -mulu(-other);
        }
        else {
            return mulu(other);
        }
    }

    Halfword Halfword::mulu(const Halfword& other) const {
        // Yet to find an algorithm for BCT (or even BCD) multiplication/division
        // so for now the multiplication and division functions are implemented
        // by converting to a native integer and back

        uint32_t a = to_uint32();
        uint32_t b = other.to_uint32();
        uint32_t c = a * b;

        return Halfword(c);
    }

    Halfword Halfword::operator/(const Halfword& other) const {
        if (is_neg() && other.is_neg()) {
            return operator-().divu(-other);
        }
        else if (is_neg()) {
            return -(operator-().divu(other));
        }
        else if (other.is_neg()) {
            return -divu(-other);
        }
        else {
            return divu(other);
        }
    }

    Halfword Halfword::divu(const Halfword& other) const {
        uint32_t a = to_uint32();
        uint32_t b = other.to_uint32();
        uint32_t c = a / b;

        return Halfword(c);
    }

    Halfword Halfword::operator~() const {
        uint32_t result_bits = 0b101010101010101010101010 - bits();
        return Halfword(from_bits, result_bits);
    }

    const Halfword Halfword::ONE(0, 1);
} // namespace termite