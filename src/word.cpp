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

    Word::Word(NativeInt, int num) 
        : hi(Tryte(native_int, num / 729)), lo(Tryte(native_int, num % 729)) {
    }

    Word::Word(Sept, const std::string &str)
        : hi(Tryte(sept, str.substr(0, 2))), lo(Tryte(sept, str.substr(2, 2))) {
    }

    Word Word::operator+(const Word& other) const {
        int result = static_cast<int>(*this) + static_cast<int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator-(const Word& other) const {
        int result = static_cast<int>(*this) - static_cast<int>(other);

        if(result < 0) {
            return Word(native_int, 531441 + (result % 531441));
        }
        
        return Word(native_int, result % 531441);
    }

    Word Word::operator*(const Word& other) const {
        int result = static_cast<int>(*this) * static_cast<int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator/(const Word& other) const {
        int result = static_cast<int>(*this) / static_cast<int>(other);
        return Word(native_int, result % 531441);
    }

    Word Word::operator%(const Word& other) const {
        int result = static_cast<int>(*this) % static_cast<int>(other);
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

    Word Word::operator>>(const Word &other) const {
        int power = 1;

        for(size_t i = 0; i < other; i++) {
            power *= 3;
        }

        return Word(native_int, operator int() / power);
    }

    Word Word::operator<<(const Word &other) const {
        int power = 1;

        for(size_t i = 0; i < other; i++) {
            power *= 3;
        }

        return Word(native_int, operator int() * power);
    }

    Tryte Word::get_hi() const {
        return hi;
    }

    Tryte Word::get_lo() const {
        return lo;
    }

    Word::operator int() const {
        return static_cast<int>(hi) * 729 + static_cast<int>(lo);
    }

    Word::operator std::string() const {
        return static_cast<std::string>(hi) + static_cast<std::string>(lo);
    }
} // namespace termite