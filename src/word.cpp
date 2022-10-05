// -*- word.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>

#include "typedefs.hpp"
#include "tryte.hpp"
#include "word.hpp"

namespace termite {
    const Word Word::ZERO(Tryte::ZERO, Tryte::ZERO);

    const Word Word::ONE(Tryte::ZERO, Tryte::ONE);

    const Word Word::TWO(Tryte::ZERO, Tryte::TWO);

    Word::Word(const Tryte& hi, const Tryte& lo)
        : hi(hi), lo(lo) {

    }

    Word Word::from_i32(i32 num) {
        if (num < 0) {
            return Word::from_u32(num + 531441);
        }

        return Word::from_u32(num);
    }

    Word Word::from_u32(u32 num) {
        u16 hi_num = num / 729;
        u16 lo_num = num % 729;

        return Word(Tryte::from_u16(hi_num), Tryte::from_u16(lo_num));
    }

    Word Word::from_sept_str(const std::string &str) {
        return Word(Tryte::from_sept_str(str.substr(0, 2)), Tryte::from_sept_str(str.substr(2, 2)));
    }

    Word Word::operator+(const Word& other) const {
        i32 result = to_i32() + other.to_i32();
        return Word::from_i32(result % 531441);
    }

    Word Word::operator-(const Word& other) const {
        i32 result = to_i32() - other.to_i32();
        return Word::from_i32(result % 531441);
    }

    Word Word::operator*(const Word& other) const {
        i32 result = to_i32() * other.to_i32();
        return Word::from_i32(result % 531441);
    }

    Word Word::umul(const Word& other) const {
        u32 result = to_u32() * other.to_u32();
        return Word::from_u32(result % 531441);
    }

    Word Word::operator/(const Word& other) const {
        i32 result = to_i32() / other.to_i32();
        return Word::from_i32(result % 531441);
    }

    Word Word::udiv(const Word& other) const {
        u32 result = to_u32() / other.to_u32();
        return Word::from_u32(result % 531441);
    }

    Word Word::operator%(const Word& other) const {
        i32 result = to_i32() % other.to_i32();
        return Word::from_i32(result % 531441);
    }

    Word Word::umod(const Word& other) const {
        u32 result = to_u32() % other.to_u32();
        return Word::from_u32(result % 531441);
    }

    Word Word::operator-() const {
        return operator~() + Word::ONE;
    }

    Word Word::operator++() {
        Word inc = operator+(Word::ONE);
        hi = inc.hi;
        lo = inc.lo;
        return *this;
    }

    Word Word::operator&(const Word& other) const {
        return Word(hi & other.hi, lo & other.lo);
    }

    Word Word::operator|(const Word& other) const {
        return Word(hi | other.hi, lo | other.lo);
    }

    Word Word::operator^(const Word& other) const {
        return Word(hi ^ other.hi, lo ^ other.lo);
    }

    Word Word::operator~() const {
        return Word(~hi, ~lo);
    }

    Tryte Word::get_hi() const {
        return hi;
    }

    Tryte Word::get_lo() const {
        return lo;
    }
    
    i32 Word::to_i32() const {
        i32 result = to_u32();

        if (result > 265720) {
            return result - 531441;
        }

        return result;
    }

    u32 Word::to_u32() const {
        return hi.to_u16() * 729 + lo.to_u16();
    }

    std::string Word::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    std::string Word::to_sept_str() const {
        return hi.to_sept_str() + lo.to_sept_str();
    }
} // namespace termite