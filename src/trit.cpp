#include <cinttypes>
#include "trit.h"

namespace termite {
    Trit::Trit() 
        : val(0) {
    }
    
    Trit::Trit(int8_t val)
        : val(val) {

    }

    Trit Trit::operator~() const {
        return Trit(2 - val);
    }

    Trit Trit::operator&(const Trit& other) const {
        return val < other.val ? Trit(val) : Trit(other.val);
    }

    Trit Trit::operator|(const Trit& other) const {
        return val > other.val ? Trit(val) : Trit(other.val);
    }


    std::pair<Trit, Trit> Trit::full_add(const Trit& other, const Trit& carry_in) const {
        int8_t temp = val + other.val + carry_in.val;
        int8_t carry_out = temp / 3;
        int8_t sum = temp % 3;
        return std::make_pair(Trit(sum), carry_out);
    }

    char Trit::to_char() const {
       return val + '0';
    }


    bool Trit::to_bool() const {
        return val == 2;
    }

} // namespace termite