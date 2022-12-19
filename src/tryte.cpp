#include <array>
#include <cinttypes>
#include <string>
#include <tuple>
#include <utility>
#include "tryte.h"

namespace termite {
    Tryte::Tryte()
        : trits(std::array<Trit, 6>()) {
    }

    Tryte::Tryte(const std::array<Trit, 6>& trits)
        : trits(trits) {
    }
    
    Tryte Tryte::from_int(int n) {
        std::array<Trit, 6> result;
        for (int i = 5; i >= 0; i--) {
            int rem = n % 3;
            n = n / 3;
            if (rem == 2) {
                rem = -1;
                n++;
            }
            result[i] = Trit(rem);
        }
        return Tryte(result);
    }

    Tryte Tryte::from_bct(uint16_t bct) {
        std::array<Trit, 6> result;

        for (int i = 5; i >= 0; i--) {
            uint16_t trit = (bct >> (2 * (5 - i))) & 3;
            result[i] = Trit(trit == 2 ? -1 : trit);
        }

        return Tryte(result);
    }

    Tryte Tryte::operator-() const {
        std::array<Trit, 6> result;

        for (int i = 5; i >= 0; i--) {
            result[i] = ~trits[i];
        }

        return Tryte(result);
    }

    Tryte Tryte::operator+(const Tryte& other) const {
        std::array<Trit, 6> result;

        Trit sum, carry;

        for (int i = 5; i >= 0; i--) {
            char old_carry = carry.to_char();
            std::tie(sum, carry) = trits[i].full_add(other.trits[i], carry);
            result[i] = sum;
        }

        return Tryte(result);
    }

    Tryte Tryte::operator-(const Tryte& other) const {
        return operator+(-other);
    }

    Tryte Tryte::operator*(const Tryte& other) const {
        Tryte result;

        for (int i = 5; i >= 0; i--) {
            Trit trit = other.trits[i];

            Tryte summand;

            if (trit.val == -1) {
                summand = -operator<<(5 - i);
            }
            else if (trit.val == 1) {
                summand = operator<<(5 - i);
            }

            result = result + summand;
        }

        return result;
    }

    std::pair<Tryte, Tryte> Tryte::operator/(const Tryte& other) const {
        Tryte remainder = *this, quotient;

        while (remainder.to_int() >= other.to_int()) {
            remainder = remainder - other;
            quotient = quotient + Tryte::from_int(1);
        }

        return std::make_pair(quotient, remainder);
    }


    Tryte Tryte::operator>>(int amount) const {
        std::array<Trit, 6> result = trits;

        for (int i = 0; i < amount; i++) {
            result = { 0, result[0], result[1], result[2], result[3], result[4] };
        }

        return Tryte(result);
    }

    Tryte Tryte::operator<<(int amount) const {
        std::array<Trit, 6> result = trits;

        for (int i = 0; i < amount; i++) {
            result = { result[1], result[2], result[3], result[4], result[5], 0 };
        }

        return Tryte(result);
    }

    int Tryte::to_int() const {
        return trits[0].val * 243
            + trits[1].val * 81
            + trits[2].val * 27
            + trits[3].val * 9
            + trits[4].val * 3
            + trits[5].val;
    }

    std::string Tryte::to_string() const {
        std::string result;

        for (int i = 0; i < 6; i++) {
            result += trits[i].to_char();
        }

        return result;
    }
} // namespace termite