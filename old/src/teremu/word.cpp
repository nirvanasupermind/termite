#include <array>
#include <cinttypes>
#include <string>
#include <utility>
#include <tuple>
#include "trit.h"
#include "tryte.h"
#include "word.h"

namespace termite {
    Word Word::from_int32(int32_t n) {
        if (n < 0) {
            // Use three's complement for negative numbers
            // https://homepage.cs.uiowa.edu/~dwjones/ternary/numbers.shtml
            return Word::from_int32(WORD_MAX + n);
        }

        Word result;
        for (int i = 0; i < WORD_TRIT; i++) {
            int r = n % 3;
            result.set_trit(i, Trit(r));
            n /= 3;
        }
        return result;
    }

    Word::Word()
        : bct(0) {


    }
    Word::Word(uint32_t bct)
        : bct(bct) {

    }

    Trit Word::get_trit(int i) const {
        return Trit((bct >> (2 * i) & 0b11));
    }

    Word Word::get_trit_range(int start, int width) const {
        uint32_t mask = ((1 << (2 * width)) - 1) << (2 * start);
        return Word((bct & mask) >> (2 * start));
    }

    void Word::set_trit(int i, const Trit& trit) {
        int shift = 2 * i;
        bct &= ~(1 << shift);
        bct |= trit.val << shift;
    }

    Word Word::operator-() const {
        return (operator~() + Word::from_int32(1)).first;
    }

    std::pair<Word, Trit> Word::operator+(const Word& other) const {
        Word result;
        Trit sum, carry;
        for (int i = 0; i < WORD_TRIT; i++) {
            std::tie(sum, carry) = get_trit(i).full_add(other.get_trit(i), carry);
            result.set_trit(i, sum);
        }
        return std::make_pair(result, carry);
    }

    std::pair<Word, Trit> Word::operator-(const Word& other) const {
        Word result;
        Trit sum, carry;
        for (int i = 0; i < WORD_TRIT; i++) {
            std::tie(sum, carry) = get_trit(i).full_add(other.get_trit(i), carry);
            result.set_trit(i, sum);
        }
        return std::make_pair(result, carry);
    }

    Word Word::operator*(const Word& other) const {
        Word result;
        for (int i = 0; i < WORD_TRIT; i++) {
            Trit trit = other.get_trit(i);
            Word addend;
            if (trit.val == 1) {
                addend = *this;
            }
            else if (trit.val == 2) {
                addend = operator+(*this).first;
            }
            result = (result + (addend << i)).first;
        }
        return result;
    }

    Word Word::operator~() const {
        Word result;
        for (int i = 0; i < WORD_TRIT; i++) {
            result.set_trit(i, ~get_trit(i));
        }
        return result;
    }

    Word Word::operator&(const Word& other) const {
        Word result;

        for (int i = 0; i < WORD_TRIT; i++) {
            result.set_trit(i, get_trit(i) & other.get_trit(i));
        }
        return result;
    }

    Word Word::operator|(const Word& other) const {
        Word result;

        for (int i = 0; i < WORD_TRIT; i++) {
            result.set_trit(i, get_trit(i) | other.get_trit(i));
        }
        return result;
    }


    Word Word::operator>>(int shift) const {
        Word result;
        for (int i = 0; i < WORD_TRIT; i++) {
            result.set_trit(i, get_trit(i + shift));
        }
        return result;
    }

    Word Word::operator<<(int shift) const {
        Word result;

        for (int i = 0; i < WORD_TRIT; i++) {
            result.set_trit(i, get_trit(i - shift));
        }
        return result;
    }


    int32_t Word::to_int32() const {
        int32_t result = 0;
        for (int i = 0; i < WORD_TRIT; i++) {
            result = result + POW3[i] * get_trit(i).val;
        }
        return result;
    }

    std::string Word::to_ternary_str() const {
        std::string result;
        for (int i = WORD_TRIT - 1; i >= 0; i--) {
            result.push_back(get_trit(i).to_char());
        }
        return result;
    }

    std::string Word::to_nonary_str() const {
        int32_t n = to_int32();
        std::string result;
        for (int i = 0; i < WORD_TRIT / 2; i++) {
            result = ((char)((n % 9) + '0')) + result;
            n = n / 9;
        }
        return result;
    }

    Word Word::lo_tryte() const {
        return Word(bct & (1 << (WORD_TRIT - 1)));
    }

    Word Word::hi_tryte() const {
        return Word(bct >> WORD_TRIT);
    }
} // namespace termite