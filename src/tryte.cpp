#include <array>
#include <iostream>
#include <tuple>
#include "tryte.h"

namespace termite {
    Tryte::Tryte(const std::array<Trit, 6>& trits)
        : trits(trits) {
    }

    Tryte::Tryte(int n) {
        for (int i = 5; i >= 0; i--) {
            int rem = n % 3;
            n = n / 3;
            if (rem == 2) {
                rem = -1;
                n++;
            }
            trits[i] = Trit(rem);
        }
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