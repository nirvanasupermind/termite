#include <cinttypes>
#include <string>
#include <tuple>
#include "trit.h"
#include "tryte.h"
#include "tables.h"
#include "word.h"

namespace termite {
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

    Trit Word::get_trit(int i) const {
        return (bct >> (i * 2)) & 3;
    }

    void Word::set_trit(int i, const Trit& val) {
        uint16_t bitmask = -(3 * (1 << (i * 2)) + 1);
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
        return operator~() + 1;
    }

    Word Word::operator+(const Word& other) const {
        Word result;

        Trit sum, carry;

        for(int i = 11; i >= 0; i--) {
            std::tie(sum, carry) = get_trit(i).full_add(other.get_trit(i), carry);
            result.set_trit(i, sum);
        }

        return result;
    }

    Word Word::operator-(const Word& other) const {
        return operator+(-other);
    }

    Word Word::operator*(const Word& other) const {
        Word result;

        for (int i = 11; i >= 0; i--) {
            Trit trit = other.get_trit(i);

            Word summand;

            if (trit.to_int() == 1) {
                summand = asr(11 - i);
            } else if(trit.to_int() == 2) {
                summand = asr(11 - i) + asr(11 - i);
            }

            result = result + summand;
        }

        return result;
    }
    

    Word Word::operator~() const {
        Word result;

        for (int i = 11; i >= 0; i--) {
            result.set_trit(i, ~get_trit(i));
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

    std::string Word::to_sep_string() const {
        return hi_tryte().to_sep_string() + lo_tryte().to_sep_string();
    }
} // namespace termite