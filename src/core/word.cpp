#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

#include "tryte.h"
#include "word.h"
#include "tables.h"

namespace termite {
    const Word Word::ONE = Word::from_int32(1);
    const Word Word::TWO = Word::from_int32(2);

    // This is the binary-coded ternary representation of 0
    Word::Word()
        : bct(0x55555555) {
    }

    Word::Word(uint32_t bct)
        : bct(bct) {

    }

    Word::Word(const Tryte& lo, const Tryte& hi)
        : bct(lo.get_bct() + (hi.get_bct() << 16)) {
    }

    uint32_t Word::get_bct() const {
        return bct;
    }

    uint8_t Word::get_bct_trit(int i) const {
        return (bct >> (2 * i)) & 3;
    }

    void Word::set_bct_trit(int i, uint8_t val) {
        bct = bct & ~(0b11 << (2 * i));
        bct = bct | (val << (2 * i));

    }

    Word Word::get_trit_range(int start, int end) const {
        Word result;
        for (int i = start; i <= end; i++) {
            result.set_bct_trit(i, get_bct_trit(i));
        }
        result = result >> Word::from_int32(start);
        return result;
    }


    Tryte Word::get_lo_tryte() const {
        return Tryte(bct & 0xffff);
    }

    Tryte Word::get_hi_tryte() const {
        return Tryte(bct >> 16);
    }

    Word Word::operator~() const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result.set_bct_trit(i, TRIT_NOT[get_bct_trit(i)]);
        }
        return result;
    }

    Word Word::operator<<(const Word& other) const {
        int32_t other_int32 = other.to_int32();
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            int temp = i - other_int32;
            if (temp < 0 || temp >= TRITS_PER_WORD) {
                continue;
            }
            else {
                result.set_bct_trit(i, get_bct_trit(temp));
            }
        }
        return result;
    }

    Word Word::operator>>(const Word& other) const {
        int32_t other_int32 = other.to_int32();
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            int temp = i + other_int32;
            if (temp < 0 || temp >= TRITS_PER_WORD) {
                continue;
            }
            else {
                result.set_bct_trit(i, get_bct_trit(temp));
            }
        }
        return result;
    }

    Word Word::operator&(const Word& other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result.set_bct_trit(i, TRIT_AND[get_bct_trit(i)][other.get_bct_trit(i)]);
        }
        return result;
    }

    Word Word::operator|(const Word& other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result.set_bct_trit(i, TRIT_OR[get_bct_trit(i)][other.get_bct_trit(i)]);
        }
        return result;
    }

    Word Word::operator^(const Word& other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result.set_bct_trit(i, TRIT_XOR[get_bct_trit(i)][other.get_bct_trit(i)]);
        }
        return result;
    }

    Word Word::operator+(const Word& other) const {
        return add_with_carry(other).first;
    }

    std::pair<Word, uint8_t> Word::add_with_carry(const Word& other) const {
        Word result;
        uint8_t sum = 0b01;
        uint8_t carry = 0b01;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            sum = TRIT_SUM[get_bct_trit(i)][other.get_bct_trit(i)][carry];
            carry = TRIT_CARRY[get_bct_trit(i)][other.get_bct_trit(i)][carry];
            result.set_bct_trit(i, sum);
        }
        return std::make_pair(result, carry);
    }

    Word Word::operator-(const Word& other) const {
        return operator+(~other);
    }

    std::pair<Word, uint8_t> Word::sub_with_carry(const Word& other) const {
        return add_with_carry(~other);
    }

    Word Word::operator*(const Word& other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            Word temp = (*this) << i;
            switch (other.get_bct_trit(i)) {
            case 0b00:
                result = result - ((*this) << termite::Word::from_int32(i));
                break;
            case 0b01:
                break;
            case 0b10:
                result = result + ((*this) << termite::Word::from_int32(i));
                break;
            default:
                break;
            }
        }
        return result;
    }

    std::string Word::to_ternary_str() const {
        std::string result = "";
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            switch (get_bct_trit(i)) {
            case 0b00:
                result = std::string("T") + result;
                break;
            case 0b01:
                result = std::string("0") + result;
                break;
            case 0b10:
                result = std::string("1") + result;
                break;
            default:
                result = std::string("?") + result;
                break;
            }
        }
        return result;
    }

    int32_t Word::to_int32() const {
        int32_t result = 0;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result += POW3[i] * ((int)(get_bct_trit(i) - 1));
        }
        return result;
    }

    Word Word::from_int32(int32_t n) {
        if (n < 0) {
            return ~Word::from_int32(-n);
        }
        Word result;
        int i = 0;
        while (n > 0) {
            int rem = n % 3;
            n = n / 3;
            if (rem == 2) {
                rem = -1;
                n++;
            }
            result.set_bct_trit(i, rem + 1);
            i++;
        }
        return result;
    }


    Word Word::from_ternary_str(const std::string& s) {
        Word result;
        for(int i = 0; i < s.size(); i++) {
            if(s.at(i) == 'T' || s.at(i) == 't') {
                result.set_bct_trit(i, 0b00);
            } else if(s.at(i) == '0') {
                result.set_bct_trit(i, 0b01);
            } else if(s.at(i) == '1') {
                result.set_bct_trit(i, 0b10);                
            } else {
               throw std::string("Malformed ternary string: " + s);
            }
        }
        return result;
    }
} // namespace termite