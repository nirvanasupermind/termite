#include <algorithm>
#include <cinttypes>
#include <utility>
#include "trit.h"

namespace termite {
    Trit::Trit() 
        : val(0) {

    }

    Trit::Trit(int8_t val)
        : val(val) {
    }

    Trit Trit::operator~() const {
        return -val;
    }

    Trit Trit::operator&(const Trit& other) const {
        return Trit(std::min(val, other.val));
    }

    Trit Trit::operator|(const Trit& other) const {
        return Trit(std::max(val, other.val));
    }

    Trit Trit::operator^(const Trit& other) const {
        return Trit(-(val * other.val));
    }

    std::pair<Trit, Trit> Trit::full_add(const Trit& other, const Trit &carry) const {
        int8_t temp = val + other.val + carry.val;
        int8_t sum = temp % 3, new_carry = temp / 3;

        if (temp == -2) {
            sum = 1;
            new_carry = -1;
        }
        else if (temp == 2) {
            sum = -1;
            new_carry = 1;
        }

        return std::make_pair(Trit(sum), Trit(new_carry));
    }

    char Trit::to_char() const {
        return val == -1 ? 'T' : (val == 0 ? '0' : '1');
    }
} // namespace termite