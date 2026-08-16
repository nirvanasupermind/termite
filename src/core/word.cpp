#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

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
    // BCT of 4782969 (minimum significand for the 32-trit floating-point numbers in terfloat.h)
    const Word Word::MIN_FLOAT_SIG(0x65555555);
    // BCT of -4782969
    const Word Word::NEG_MIN_FLOAT_SIG(0x45555555);
    // BCT of 14348907 (maximum significand for the 32-trit floating-point numbers in terfloat.h)
    const Word Word::MAX_FLOAT_SIG(0x95555555);
    // BCT of -14348907
    const Word Word::NEG_MAX_FLOAT_SIG(0x15555555);
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

    Word Word::shl_int8(int8_t other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            int temp = i - other;
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

    Word Word::shr_int8(int8_t other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            int temp = i + other;
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

    std::pair<Word, uint8_t> Word::sub_with_borrow(const Word& other) const {
        return add_with_carry(-other);
    }

    Word Word::operator*(const Word& other) const {
        Word result;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            Word shifted = shl_int8(i);
            switch (other.get_bct_trit(i)) {
            case 0b00:
                result = result - shifted;
                break;
            case 0b01:
                break;
            case 0b10:
                result = result + shifted;
                break;
            default:
                break;
            }
        }
        return result;
    }

//     std::pair<Word, Word> Word::mul32(const Word& other) const {
//     Word lo = Word::ZERO;
//     Word hi = Word::ZERO;

//     for (int i = 0; i < TRITS_PER_WORD; ++i) {
//         std::cout << "DBG212 " << i << '\n';
//         Word shifted_lo = shl_int8(i);

//         Word shifted_hi = Word::ZERO;
//         if (i > 0) {
//             shifted_hi = shr_int8(TRITS_PER_WORD - i);
//         }

//         uint8_t trit = other.get_bct_trit(i);

//         if (trit == 0b10) {
//             // Add this * 3^i
//             auto [new_lo, carry_trit] =
//                 lo.add_with_carry(shifted_lo);

//             lo = new_lo;

//             int carry_value =
//                 static_cast<int>(carry_trit) - 1;

//             hi = hi
//                + shifted_hi
//                + Word::from_int32(carry_value);
//         }
//         else if (trit == 0b00) {
//             // Subtract this * 3^i
//             auto [new_lo, carry_trit] =
//                 lo.sub_with_borrow(shifted_lo);

//             lo = new_lo;

//             int carry_value =
//                 static_cast<int>(carry_trit) - 1;

//             hi = hi
//                - shifted_hi
//                + Word::from_int32(carry_value);
//         }
//     }

//     return {lo, hi};
// }
    std::pair<Word, Word> Word::mul32(const Word& other) const {
        Word result;
        Word carry;
        for (int i = 0; i < TRITS_PER_WORD; i++) {
            Word shifted = shl_int8(i);
            switch (other.get_bct_trit(i)) {
            case 0b00: {
                std::pair<Word, uint8_t> temp_pair = result.sub_with_borrow(shifted);
                result = temp_pair.first;
                int carry_value = static_cast<int>(temp_pair.second) - 1;
                carry = carry + Word::from_int32(carry_value).shl_int8(i);
                break;
            }
            case 0b01:
                break;
            case 0b10: {
                std::pair<Word, uint8_t> temp_pair = result.add_with_carry(shifted);
                result = temp_pair.first;
                int carry_value = static_cast<int>(temp_pair.second) - 1;
                carry = carry + Word::from_int32(carry_value).shl_int8(i);
                break;
            }
            default:
                break;
            }
        }
        return std::pair<Word, Word>(result, carry);
    }

    // // TEMPORARY VERSION
    // // I WILL FIGURE OUT HOW TO ACTUALLY DO THIS WITHOUT CONVERTING TO BINARY INT LATER 
    // int64_t i64_result = (int64_t)(to_int32()) * (int64_t)(other.to_int32());
    // int64_t i64_hi = (i64_result + 21523360) / 43046721;
    // int64_t i64_lo = i64_result - i64_hi * 43046721;
    // return {Word::from_int32(i64_lo), Word::from_int32(i64_hi)};

    Word Word::operator/(const Word& other) const {
        return divmod(other).first;
    }

    Word Word::operator%(const Word& other) const {
        return divmod(other).second;
    }

    std::pair<Word, Word> Word::divmod(const Word& other) const {
        if(other == Word::ZERO) {
            throw std::string("Ternary math error - Integer division by zero");
        }

        if(other < Word::ZERO) {
            return divmod(-other);
        }

        if(*this < Word::ZERO) {
            Word neg_this = -(*this);
            std::pair<Word, Word> neg_this_dm_other = neg_this.divmod(other);
            return std::make_pair(-(neg_this_dm_other.first + Word::ONE),other-neg_this_dm_other.second);
        }

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
        // return to_int32() == other.to_int32();
        return bct == other.bct;
    }


    bool Word::operator!=(const Word& other) const {
        // return to_int32() != other.to_int32();
        return bct != other.bct;
    }


    bool Word::operator>(const Word& other) const {
        // return to_int32() > other.to_int32();
        // Luckily, comparing the BCT encodings works for comparison
        return bct > other.bct;
    }

    bool Word::operator>=(const Word& other) const {
        // return to_int32() >= other.to_int32();
        return bct >= other.bct;
    }

    bool Word::operator<(const Word& other) const {
        // return to_int32() < other.to_int32();
        return bct < other.bct;
    }

    bool Word::operator<=(const Word& other) const {
        // return to_int32() <= other.to_int32();
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
        for(int i = 0; i < s.size(); i++) {
            char ch = s.at(s.size() - i - 1);
            if(ch == 'A' || s.at(i) == 'a') {
                result.set_bct_trit(i, 0b00);
            } else if(ch == '0') {
                result.set_bct_trit(i, 0b01);
            } else if(ch == '1') {
                result.set_bct_trit(i, 0b10);                
            } else {
               throw std::string("Malformed ternary string: " + s);
            }
        }
        return result;
    }

    Word Word::from_nonary_str(const std::string& s) {
        Word result;
        for(int i = 0; i < s.size(); i++) {
            char ch = s.at(s.size() - i - 1);
            if(ch == 'D') {
                result.set_bct_trit(2 * i + 1, 0b00);
                result.set_bct_trit(2 * i, 0b00);
            } else if(ch == 'C') {
                result.set_bct_trit(2 * i + 1, 0b00);
                result.set_bct_trit(2 * i , 0b01);
            } else if(ch == 'B') {
                result.set_bct_trit(2 * i + 1, 0b00);
                result.set_bct_trit(2 * i, 0b10);
            } else if(ch == 'A') {
                result.set_bct_trit(2 * i + 1, 0b01);
                result.set_bct_trit(2 * i, 0b00);
            } else if(ch == '0') {
                result.set_bct_trit(2 * i + 1, 0b01);
                result.set_bct_trit(2 * i, 0b01);
            } else if(ch == '1') {
                result.set_bct_trit(2 * i + 1, 0b01);
                result.set_bct_trit(2 * i, 0b10);
            } else if(ch == '2') {
                result.set_bct_trit(2 * i + 1, 0b10);
                result.set_bct_trit(2 * i, 0b00);
            } else if(ch == '3') {
                result.set_bct_trit(2 * i + 1, 0b10);
                result.set_bct_trit(2 * i, 0b01);
            } else if(ch == '4') {
                result.set_bct_trit(2 * i + 1, 0b10);
                result.set_bct_trit(2 * i, 0b10);
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

// #include <cstdint>
// #include <string>
// #include <iostream>
// #include <algorithm>
// #include <utility>

// #include "tryte.h"
// #include "word.h"
// #include "tables.h"

// namespace termite {
//     const Word Word::ZERO(0x55555555);
//     // This is the binary-coded ternary representation of 1
//     const Word Word::ONE(0x55555556);
//     // BCT for 2
//     const Word Word::TWO(0x55555558);

//     // BCT for 0
//     Word::Word()
//         : bct(0x55555555) {
//     }

//     Word::Word(uint32_t bct)
//         : bct(bct) {

//     }

//     Word::Word(const Tryte& lo, const Tryte& hi)
//         : bct(lo.get_bct() + (hi.get_bct() << 16)) {
//     }

//     uint32_t Word::get_bct() const {
//         return bct;
//     }

//     uint8_t Word::get_bct_trit(int i) const {
//         return (bct >> (2 * i)) & 3;
//     }

//     void Word::set_bct_trit(int i, uint8_t val) {
//         bct = bct & ~(0b11 << (2 * i));
//         bct = bct | (val << (2 * i));

//     }

//     Word Word::get_trit_range(int start, int end) const {
//         Word result;
//         for (int i = start; i <= end; i++) {
//             result.set_bct_trit(i, get_bct_trit(i));
//         }
//         result = result >> Word::from_int32(start);
//         return result;
//     }


//     Tryte Word::get_lo_tryte() const {
//         return Tryte(bct & 0xffff);
//     }

//     Tryte Word::get_hi_tryte() const {
//         return Tryte(bct >> 16);
//     }

//     Word Word::operator-() const {
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             result.set_bct_trit(i, TRIT_NOT[get_bct_trit(i)]);
//         }
//         return result;
//     }

//     Word Word::operator<<(const Word& other) const {
//         int32_t other_int32 = other.to_int32();
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             int temp = i - other_int32;
//             if (temp < 0 || temp >= TRITS_PER_WORD) {
//                 continue;
//             }
//             else {
//                 result.set_bct_trit(i, get_bct_trit(temp));
//             }
//         }
//         return result;
//     }

//     Word Word::operator>>(const Word& other) const {
//         int32_t other_int32 = other.to_int32();
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             int temp = i + other_int32;
//             if (temp < 0 || temp >= TRITS_PER_WORD) {
//                 continue;
//             }
//             else {
//                 result.set_bct_trit(i, get_bct_trit(temp));
//             }
//         }
//         return result;
//     }

//     Word Word::operator&(const Word& other) const {
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             result.set_bct_trit(i, TRIT_AND[get_bct_trit(i)][other.get_bct_trit(i)]);
//         }
//         return result;
//     }

//     Word Word::operator|(const Word& other) const {
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             result.set_bct_trit(i, TRIT_OR[get_bct_trit(i)][other.get_bct_trit(i)]);
//         }
//         return result;
//     }

//     Word Word::operator^(const Word& other) const {
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             result.set_bct_trit(i, TRIT_XOR[get_bct_trit(i)][other.get_bct_trit(i)]);
//         }
//         return result;
//     }

//     Word Word::operator+(const Word& other) const {
//         return add_with_carry(other).first;
//     }

//     std::pair<Word, uint8_t> Word::add_with_carry(const Word& other) const {
//         Word result;
//         uint8_t sum = 0b01;
//         uint8_t carry = 0b01;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             sum = TRIT_SUM[get_bct_trit(i)][other.get_bct_trit(i)][carry];
//             carry = TRIT_CARRY[get_bct_trit(i)][other.get_bct_trit(i)][carry];
//             result.set_bct_trit(i, sum);
//         }
//         return std::make_pair(result, carry);
//     }

//     Word Word::operator-(const Word& other) const {
//         return operator+(-other);
//     }

//     std::pair<Word, uint8_t> Word::sub_with_carry(const Word& other) const {
//         return add_with_carry(-other);
//     }

//     Word Word::operator*(const Word& other) const {
//         Word result;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             Word temp = (*this) << i;
//             switch (other.get_bct_trit(i)) {
//             case 0b00:
//                 result = result - ((*this) << termite::Word::from_int32(i));
//                 break;
//             case 0b01:
//                 break;
//             case 0b10:
//                 result = result + ((*this) << termite::Word::from_int32(i));
//                 break;
//             default:
//                 break;
//             }
//         }
//         return result;
//     }


//     std::pair<Word, Word> Word::mul32(const Word& other) const {
//         Word low, high;

//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             Word shifted = (*this) << Word::from_int32(i);

//             switch (other.get_bct_trit(i)) {
//             case 0b00: // -1 in balanced ternary
//                 std::tie(low, high) = low.sub_with_carry(shifted);
//                 break;
//             case 0b01: //  0 in balanced ternary (no effect)
//                 break;
//             case 0b10: //  1 in balanced ternary
//                 std::tie(low, high) = low.add_with_carry(shifted);
//                 break;
//             default:
//                 break;
//             }
//         }

//         return std::make_pair(low, high);
//     }


//     Word Word::operator/(const Word& other) const {
//         Word rem(bct);
//         Word quo;
//         while(rem.to_int32() >= other.to_int32()) {
//             rem = rem - other;
//             quo = quo + Word::ONE;
//         }
//         return quo;
//     }

//     Word Word::operator%(const Word& other) const {
//         Word rem(bct);
//         while(rem.to_int32() >= other.to_int32()) {
//             rem = rem - other;
//         }
//         return rem;
//     }

//     std::pair<Word, Word> Word::divmod(const Word& other) const {
//         std::pair<Word, Word> result;
//         Word rem(bct);
//         Word quo;
//         while(rem.to_int32() >= other.to_int32()) {
//             rem = rem - other;
//             quo = quo + Word::ONE;
//         }
//         return std::make_pair(quo, rem);
//     }

//     bool Word::operator==(const Word& other) const {
//         return bct == other.bct;
//     }


//     bool Word::operator!=(const Word& other) const {
//         return bct != other.bct;
//     }

//     bool Word::operator>(const Word& other) const {
//         // Luckily, comparing the BCT encodings works for comparison
//         return bct > other.bct;
//     }

//     bool Word::operator>=(const Word& other) const {
//         return bct >= other.bct;
//     }

//     bool Word::operator<(const Word& other) const {
//         return bct < other.bct;
//     }

//     bool Word::operator<=(const Word& other) const {
//         return bct <= other.bct;
//     }

//     std::string Word::to_ternary_str() const {
//         std::string result = "";
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             switch (get_bct_trit(i)) {
//             case 0b00:
//                 result = std::string("T") + result;
//                 break;
//             case 0b01:
//                 result = std::string("0") + result;
//                 break;
//             case 0b10:
//                 result = std::string("1") + result;
//                 break;
//             default:
//                 result = std::string("?") + result;
//                 break;
//             }
//         }
//         return result;
//     }

//     int32_t Word::to_int32() const {
//         int32_t result = 0;
//         for (int i = 0; i < TRITS_PER_WORD; i++) {
//             result += POW3[i] * ((int)(get_bct_trit(i) - 1));
//         }
//         return result;
//     }

//     Word Word::from_int32(int32_t n) {
//         if (n < 0) {
//             return -Word::from_int32(-n);
//         }
//         Word result;
//         int i = 0;
//         while (n > 0) {
//             int rem = n % 3;
//             n = n / 3;
//             if (rem == 2) {
//                 rem = -1;
//                 n++;
//             }
//             result.set_bct_trit(i, rem + 1);
//             i++;
//         }
//         return result;
//     }


//     Word Word::from_ternary_str(const std::string& s) {
//         Word result;
//         for(int i = 0; i < s.size(); i++) {
//             char ch = s.at(s.size() - i - 1);
//             if(ch == 'T' || s.at(i) == 't') {
//                 result.set_bct_trit(i, 0b00);
//             } else if(ch == '0') {
//                 result.set_bct_trit(i, 0b01);
//             } else if(ch == '1') {
//                 result.set_bct_trit(i, 0b10);                
//             } else {
//                throw std::string("Malformed ternary string: " + s);
//             }
//         }
//         return result;
//     }
// } // namespace termite