#include <cinttypes>
#include <string>
#include <tuple>
#include <utility>
#include <iostream>
#include "trit.h"
#include "tryte.h"
#include "tables.h"
#include "word.h"

namespace termite {
    const Word Word::ZERO = Word::from_int(0);

    const Word Word::ONE = Word::from_int(1);

    Word::Word(uint32_t bct)
        : bct(bct) {
    }
    
    Word Word::from_int(int val) {
        if (val < 0) {
            return Word::from_int(Word::MAX + val);
        }
        else {
            Word result;
            for (int i = 0; i < 12; i++) {
                result.set_trit(i, Trit(val % 3));
                val /= 3;
            }
            return result;
        }
    }

    Word Word::from_trytes(const Tryte& hi, const Tryte& lo) {
        return Word::from_int(hi.to_int() * 729 + lo.to_int());
    }

    Trit Word::get_trit(int i) const {
        return (bct >> (i * 2)) & 3;
    }

    void Word::set_trit(int i, const Trit& val) {
        uint32_t bitmask = -(3 * (1 << (i * 2)) + 1);
        bct = (bct & bitmask) + (val.to_int() << (i * 2));
    }

    Tryte Word::hi_tryte() const {
        return Tryte(bct >> 12);
    }

    Tryte Word::lo_tryte() const {
        return Tryte(bct & 0xfff);
    }

    bool Word::is_neg() const {
        return to_int() > (Word::MAX / 2);
    }

    Word Word::operator-() const {
        return (operator~() + Word::from_int(1)).first;
    }

    std::pair<Word, Trit> Word::operator+(const Word& other) const {
        Word result;

        Trit sum, carry;

        for(int i = 0; i < 12; i++) {
            std::tie(sum, carry) = get_trit(i).full_add(other.get_trit(i), carry);
            result.set_trit(i, sum);
        }

        return std::make_pair(result, carry);
    }

    std::pair<Word, Trit> Word::operator-(const Word& other) const {
        return operator+(-other);
    }

    Word Word::operator*(const Word& other) const {
        Word result;

        for (int i = 0; i < 12; i++) {
            Trit trit = other.get_trit(i);

            Word summand;

            if (trit.to_int() == 1) {
                summand = asr(i);
            } else if(trit.to_int() == 2) {
                summand = (asr(i) + asr(i)).first;
            }
            result = (result + summand).first;
        }

        return result;
    }

    std::pair<Word, Word> Word::udiv(const Word& other) const {
        int i = 0;
        Word remainder = *this, quotient;

        while (remainder.to_int() >= other.to_int()) {
            remainder = (remainder - other).first;
            quotient = (quotient + Word::from_int(1)).first;
            i++;
        }

        return std::make_pair(quotient, remainder);
    }

    std::pair<Word, Word> Word::sdiv(const Word& other) const {
        if(is_neg() && other.is_neg()) {
            return operator-().udiv(-other);
        } else if(is_neg() && !other.is_neg()) {
            return std::make_pair(-operator-().udiv(other).first, -operator-().udiv(other).second);
        } else if(!is_neg() && other.is_neg()) {
            return std::make_pair(-udiv(-other).first, -udiv(-other).second);
        } else {
            return udiv(other);
        }
    }

    Word Word::operator~() const {
        Word result;

        for (int i = 0; i < 12; i++) {
            result.set_trit(i, ~get_trit(i));
        }

        return result;
    }

    Word Word::operator&(const Word& other) const {
        Word result;

        for (int i = 0; i < 12; i++) {
            result.set_trit(i, get_trit(i) & other.get_trit(i));
        }

        return result;
    }

    Word Word::operator|(const Word& other) const {
        Word result;

        for (int i = 0; i < 12; i++) {
            result.set_trit(i, get_trit(i) | other.get_trit(i));
        }

        return result;
    }

    Word Word::operator^(const Word& other) const {
        Word result;

        for (int i = 0; i < 12; i++) {
            result.set_trit(i, get_trit(i) ^ other.get_trit(i));
        }

        return result;
    }

    Word Word::operator>>(int amount) const {
        return Word(bct >> (amount * 2));
    }

    Word Word::lsr(int amount) const {
        return Word(bct << (amount * 2));
    }

    Word Word::asr(int amount) const {
        if(is_neg()) {
            return -(operator-().lsr(amount));
        } else {
            return lsr(amount);
        }
    }

    int Word::to_int() const {
        int result = 0;

        for (int i = 0; i < 12; i++) {
            result += get_trit(i).to_int() * POW3.at(i);
        }

        return result;
    }

    std::string Word::to_ter_string() const {
        std::string result;

        for (int i = 11; i >= 0; i--) {
            result += get_trit(i).to_char();
        }

        return result;
    }

    std::string Word::to_non_string() const {
        return hi_tryte().to_non_string() + lo_tryte().to_non_string();
    }
} // namespace termite