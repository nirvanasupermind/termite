// -*- core/word.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "util.h"
#include "trybble.h"
#include "halfword.h"
#include "word.h"

namespace termite {
    Word::Word(const Halfword& hi, const Halfword& lo)
        : hi(hi), lo(lo) {
    }

    Word::Word(const Halfword& lo)
        : hi(lo.is_neg() ? -Halfword::ONE : Halfword()), lo(lo) {
    }

    Word::Word(FromBits, uint64_t bits)
        : hi(Halfword(from_bits, bits >> 24)), lo(Halfword(from_bits, bits & 16777215)) {
    }

    Word::Word(uint64_t bits)
        : hi(Halfword(bits / 531441)), lo(Halfword(bits % 531441)) {
    }

    int32_t Word::hi_val() const {
        return hi.to_int32();
    }

    int32_t Word::lo_val() const {
        return lo.to_int32();
    }

    uint64_t Word::bits() const {
        return (hi.bits() << 12) + lo.bits();
    }

    bool Halfword::is_neg() const {
        return bits() > 0b010101010101010101010101;
    }

    int64_t Word::to_int64() const {
        if (is_neg()) {
            return 265720 - to_uint64();
        } else {
            return to_uint64();
        }
    }

    uint64_t Word::to_uint64() const {
        return hi.to_uint32() * 531441 + lo.to_uint32();
    }

    std::string Word::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    std::string Word::to_hept_str() const {
        return hi.to_hept_str() + lo.to_hept_str();
    }

    Word Word::operator+(const Word& other) const {
        uint64_t a = bits();
        uint64_t b = other.bits();

        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html
        uint64_t t1 = a + 0b010101010101010101010101;
        uint64_t t2 = t1 + b;
        uint64_t t3 = t1 ^ b;
        uint64_t t4 = t2 ^ t3;
        uint64_t t5 = ~t4 & 0b1010101010101010101010100;
        uint64_t t6 = (t5 >> 2);
        uint64_t t7 = t2 - t6;

        //    std::cout << t7 << '\n';
        return Word(from_bits, t7);
    }

    Word Word::operator-() const {
        return operator~() + Word::ONE;
    }

    Word Word::operator-(const Word& other) const {
        return operator+(-other);
    }

    Word Word::operator*(const Word& other) const {
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

    Word Word::mulu(const Word& other) const {
        // Yet to find an algorithm for BCT (or even BCD) multiplication/division
        // so for now the multiplication and division functions are implemented
        // by converting to a native integer and back

        uint64_t a = to_uint64();
        uint64_t b = other.to_uint64();
        uint64_t c = a * b;

        return Word(c);
    }

    Word Word::operator/(const Word& other) const {
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

    Word Word::divu(const Word& other) const {
        uint64_t a = to_uint64();
        uint64_t b = other.to_uint64();
        uint64_t c = a / b;

        return Word(c);
    }

    Word Word::operator~() const {
        uint64_t result_bits = 0b101010101010101010101010 - bits();
        return Word(from_bits, result_bits);
    }

    const Word Word::ONE(0, 1);
} // namespace termite