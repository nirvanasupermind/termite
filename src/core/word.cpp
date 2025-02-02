#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

#include "tryte.h"
#include "word.h"
#include "tables.h"

namespace termite {
    // This is the binary-coded ternary representation of 0
    const Word Word::ZERO(0x55555555);
    // BCT of 1
    const Word Word::ONE(0x55555556);
    // BCT of 2
    const Word Word::TWO(0x55555558);

    // BCT of 0
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

    Word Word::operator-() const {
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
        return operator+(-other);
    }

    std::pair<Word, uint8_t> Word::sub_with_carry(const Word& other) const {
        return add_with_carry(-other);
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


    std::pair<Word, Word> Word::mul32(const Word& other) const {
        Word low, high;

        for (int i = 0; i < TRITS_PER_WORD; i++) {
            Word shifted = (*this) << Word::from_int32(i);

            switch (other.get_bct_trit(i)) {
            case 0b00: // -1 in balanced ternary
                std::tie(low, high) = low.sub_with_carry(shifted);
                break;
            case 0b01: //  0 in balanced ternary (no effect)
                break;
            case 0b10: //  1 in balanced ternary
                std::tie(low, high) = low.add_with_carry(shifted);
                break;
            default:
                break;
            }
        }

        return std::make_pair(low, high);
    }


    Word Word::operator/(const Word& other) const {
        Word rem(bct);
        Word quo;
        while(rem.to_int32() >= other.to_int32()) {
            rem = rem - other;
            quo = quo + Word::ONE;
        }
        return quo;
    }

    Word Word::operator%(const Word& other) const {
        Word rem(bct);
        while(rem.to_int32() >= other.to_int32()) {
            rem = rem - other;
        }
        return rem;
    }

    std::pair<Word, Word> Word::divmod(const Word& other) const {
        std::pair<Word, Word> result;
        Word rem(bct);
        Word quo;
        while(rem.to_int32() >= other.to_int32()) {
            rem = rem - other;
            quo = quo + Word::ONE;
        }
        return std::make_pair(quo, rem);
    }


    bool Word::operator==(const Word& other) const {
        return bct == other.bct;
    }


    bool Word::operator!=(const Word& other) const {
        return bct != other.bct;
    }


    bool Word::operator>(const Word& other) const {
        // Luckily, comparing the BCT encodings works for comparison
        return bct > other.bct;
    }

    bool Word::operator>=(const Word& other) const {
        return bct >= other.bct;
    }

    bool Word::operator<(const Word& other) const {
        return bct < other.bct;
    }

    bool Word::operator<=(const Word& other) const {
        return bct <= other.bct;
    }

    std::string Word::to_ternary_str() const {
        std::string result = "";
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            result = TRIT_TO_TERNARY_CH[get_bct_trit(i)] + result;
        }
        return result;
    }

    std::string Word::to_nonary_str() const {
        std::string result = "";
        for (int i = 0; i < TRITS_PER_WORD; i += 2) {
            result = TRITS_TO_NONARY_CH[get_bct_trit(i + 1)][get_bct_trit(i)] + result;
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
            return -Word::from_int32(-n);
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
        for(int i = s.size() - 1; i >= 0; i--) {
            int j = (s.size() - 1) - i;
            if(s.at(i) == 'A' || s.at(i) == 'a') {
                result.set_bct_trit(j, 0b00);
            } else if(s.at(i) == '0') {
                result.set_bct_trit(j, 0b01);
            } else if(s.at(i) == '1') {
                result.set_bct_trit(j, 0b10);                
            } else {
               throw std::string("Malformed ternary string: " + s);
            }
        }
        return result;
    }

    Word Word::from_nonary_str(const std::string& s) {
        Word result;
        for(int i = s.size() - 1; i >= 0; i--) {
            int j = (s.size() - 1) - i;
            if(s.at(i) == 'D') {
                result.set_bct_trit(2 * j + 1, 0b00);
                result.set_bct_trit(2 * j, 0b00);
            } else if(s.at(i) == 'C') {
                result.set_bct_trit(2 * j + 1, 0b00);
                result.set_bct_trit(2 * j , 0b01);
            } else if(s.at(i) == 'B') {
                result.set_bct_trit(2 * j + 1, 0b00);
                result.set_bct_trit(2 * j, 0b10);
            } else if(s.at(i) == 'A') {
                result.set_bct_trit(2 * j + 1, 0b01);
                result.set_bct_trit(2 * j, 0b00);
            } else if(s.at(i) == '0') {
                result.set_bct_trit(2 * j + 1, 0b01);
                result.set_bct_trit(2 * j, 0b01);
            } else if(s.at(i) == '1') {
                result.set_bct_trit(2 * j + 1, 0b01);
                result.set_bct_trit(2 * j, 0b10);
            } else if(s.at(i) == '2') {
                result.set_bct_trit(2 * j + 1, 0b10);
                result.set_bct_trit(2 * j, 0b00);
            } else if(s.at(i) == '3') {
                result.set_bct_trit(2 * j + 1, 0b10);
                result.set_bct_trit(2 * j, 0b01);
            } else if(s.at(i) == '4') {
                result.set_bct_trit(2 * j + 1, 0b10);
                result.set_bct_trit(2 * j, 0b10);
            } else {
               throw std::string("Malformed nonary string: " + s);
            }
            // if(s.at(i) == 'D') {
            //     result.set_bct_trit(2 * j, 0b00);
            //     result.set_bct_trit(2 * j + 1, 0b00);
            // } else if(s.at(i) == 'C') {
            //     result.set_bct_trit(2 * j, 0b00);
            //     result.set_bct_trit(2 * j + 1, 0b01);
            // } else if(s.at(i) == 'B') {
            //     result.set_bct_trit(2 * j, 0b00);
            //     result.set_bct_trit(2 * j + 1, 0b10);
            // } else if(s.at(i) == 'A') {
            //     result.set_bct_trit(2 * j, 0b01);
            //     result.set_bct_trit(2 * j + 1, 0b00);
            // } else if(s.at(i) == '0') {
            //     result.set_bct_trit(2 * j, 0b01);
            //     result.set_bct_trit(2 * j + 1, 0b01);
            // } else if(s.at(i) == '1') {
            //     result.set_bct_trit(2 * j, 0b01);
            //     result.set_bct_trit(2 * j + 1, 0b10);
            // } else if(s.at(i) == '2') {
            //     result.set_bct_trit(2 * j, 0b10);
            //     result.set_bct_trit(2 * j + 1, 0b00);
            // } else if(s.at(i) == '3') {
            //     result.set_bct_trit(2 * j, 0b10);
            //     result.set_bct_trit(2 * j + 1, 0b01);
            // } else if(s.at(i) == '4') {
            //     result.set_bct_trit(2 * j, 0b10);
            //     result.set_bct_trit(2 * j + 1, 0b10);
            // } else {
            //    throw std::string("Malformed nonary string: " + s);
            // }
        }
        return result;
    }
} // namespace termite