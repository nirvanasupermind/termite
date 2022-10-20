// -*- word.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>

#include "util.hpp"
#include "tryte.hpp"
#include "word.hpp"

namespace termite {
    const Word Word::ZERO(Tryte::ZERO, Tryte::ZERO);

    const Word Word::ONE(Tryte::ZERO, Tryte::ONE);

    const Word Word::TWO(Tryte::ZERO, Tryte::TWO);

    Word::Word(const Tryte& hi, const Tryte& lo)
        : hi(hi), lo(lo) {

    }

    Word::Word(NativeInt, unsigned int num) 
        : hi(Tryte(native_int, num / 729)), lo(Tryte(native_int, num % 729)) {
    }

    Word::Word(Sept, const std::string &str)
        : hi(Tryte(sept, str.substr(0, 2))), lo(Tryte(sept, str.substr(2, 2))) {
    }

    Word Word::operator+(const Word& other) const {
        unsigned int result = static_cast<unsigned int>(*this) + static_cast<unsigned int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator-(const Word& other) const {
        int result = static_cast<unsigned int>(*this) - static_cast<unsigned int>(other);

        if(result < 0) {
            return Word(native_int, 531441 + (result % 531441));
        }
        
        return Word(native_int, result % 531441);
    }

    Word Word::operator*(const Word& other) const {
        unsigned int result = static_cast<unsigned int>(*this) * static_cast<unsigned int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator/(const Word& other) const {
        unsigned int result = static_cast<unsigned int>(*this) / static_cast<unsigned int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator%(const Word& other) const {
        unsigned int result = static_cast<unsigned int>(*this) % static_cast<unsigned int>(other);
        return Word(native_int, result % 531441);
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

    Word::operator unsigned int() const {
        return static_cast<unsigned int>(hi) * 729 + static_cast<unsigned int>(lo);
    }

    Word::operator std::string() const {
        return static_cast<std::string>(hi) + static_cast<std::string>(lo);
    }
} // namespace termite