// -*- word.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>

#include "typedefs.hpp"
#include "tryte.hpp"
#include "word.hpp"

namespace termite {
    const Word Word::ZERO(Tryte::ZERO, Tryte::ZERO, Tryte::ZERO);

    const Word Word::ONE(Tryte::ZERO, Tryte::ZERO, Tryte::ONE);

    Word::Word(const Tryte& hi, const Tryte& mid, const Tryte& lo)
        : hi(hi), mid(mid), lo(lo) {

    }

    Word Word::from_i32(i32 num) {
        if (num < 0) {
            return Word::from_u32(num + 387420489);
        }

        return Word::from_u32(num);
    }

    Word Word::from_u32(u32 num) {
        u32 hi_num = num / 531441;
        u32 temp = num % 531441;
        u32 mid_num = temp / 729;
        u32 lo_num = temp % 729;

        return Word(Tryte::from_u16(hi_num), Tryte::from_u16(mid_num), Tryte::from_u16(lo_num));
    }

    Word Word::operator+(const Word& other) const {
        return Word::from_i32((to_i32() + other.to_i32()) % 387420489);
    }

    Word Word::operator-(const Word& other) const {
        return Word::from_i32((to_i32() - other.to_i32()) % 387420489);
    }

    Word Word::operator*(const Word& other) const {
        return Word::from_i32(((i64)to_i32() * (i64)other.to_i32()) % 387420489);
    }

    Word Word::mulu(const Word& other) const {
        return Word::from_u32(((u64)to_u32() * (u64)other.to_u32()) % 387420489);
    }

    Word Word::operator/(const Word& other) const {
        return Word::from_i32((to_i32() / other.to_i32()) % 387420489);
    }

    Word Word::divu(const Word& other) const {
        return Word::from_u32((to_u32() / other.to_u32()) % 387420489);
    }

    Word Word::operator%(const Word& other) const {
        return Word::from_i32((to_i32() % other.to_i32()) % 387420489);
    }

    Word Word::modu(const Word& other) const {
        return Word::from_u32((to_u32() % other.to_u32()) % 387420489);
    }

    Word Word::operator-() const {
        return operator~() + Word::ONE;
    }

    Word Word::operator&(const Word& other) const {
        return Word(hi & other.hi, mid & other.mid, lo & other.lo);
    }

    Word Word::operator|(const Word& other) const {
        return Word(hi | other.hi, mid | other.mid, lo | other.lo);
    }

    Word Word::operator^(const Word& other) const {
        return Word(hi ^ other.hi, mid ^ other.mid, lo ^ other.lo);
    }

    Word Word::operator~() const {
        return Word(~hi, ~mid, ~lo);
    }

    Tryte Word::get_hi() const {
        return hi;
    }

    Tryte Word::get_mid() const {
        return mid;
    }

    Tryte Word::get_lo() const {
        return lo;
    }
    
    i32 Word::to_i32() const {
        i32 result = to_u32();

        if (result > 193710244) {
            return result - 387420489;
        }

        return result;
    }

    u32 Word::to_u32() const {
        return hi.to_u16() * 531441 + mid.to_u16() * 729 + lo.to_u16();
    }

    std::string Word::to_ternary_str() const {
        return hi.to_ternary_str() + mid.to_ternary_str() + lo.to_ternary_str();
    }

    std::string Word::to_sept_str() const {
        return hi.to_sept_str() + mid.to_sept_str() + lo.to_sept_str();
    }
} // namespace termite