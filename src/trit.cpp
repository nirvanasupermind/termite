#include <algorithm>
#include <utility>
#include "trit.h"

namespace termite {
    Trit::Trit(int val)
        : val(val) {
    }

    Trit Trit::operator~() const {
        return Trit(-val);
    }

    Trit Trit::operator&(const Trit& other) const {
        return Trit(std::min(val, other.val));
    }

    Trit Trit::operator|(const Trit& other) const {
        return Trit(std::max(val, other.val));
    }

    Trit Trit::operator^(const Trit& other) const {
        return Trit(val * (-other.val) + val + other.val);
    }

    std::pair<Trit, Trit> Trit::full_add(const Trit& other, const Trit& carry_in) const {
        int temp = (val + other.val + carry_in.val),
            sum = temp % 3,
            carry = temp / 3;

        return std::make_pair(sum, carry);
    }

    int Trit::to_int() const {
        return val;
    }

    char Trit::to_char() const {
        return val + 48;
    }
} // namespace termite