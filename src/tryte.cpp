#include <cinttypes>
#include <string>
#include "trit.h"
#include "tryte.h"

namespace termite {
    Tryte Tryte::from_int(int n) {
        if(n < 0) {
            return Tryte::from_int(TRYTE_MAX + n);
        }

        Tryte result;
        for(int i = 0; i < TRYTE_TRIT; i++) {
            int r = n % 3;
            result.set_trit(i, Trit(r));
            n /= 3;
        }
        return result;
    }

    Tryte::Tryte() 
        : bct(0) {


    }
    Tryte::Tryte(uint16_t bct) 
        : bct(bct) {

    }

    Tryte Tryte::operator-() const {
        Tryte result;
        for(int i = 0; i < TRYTE_TRIT; i++) {
            result.set_trit(i, ~get_trit(i));
        }
        return result;
    }


    int Tryte::to_int() const {
        int result = 0;
        for (int i = 0; i < TRYTE_TRIT; i++) {
            result = result + POW3[i] * get_trit(i).val;
        }
        return result;
    }

    Trit Tryte::get_trit(int i) const {
        return Trit((bct >> (2 * i) & 0b11));
    }
    
    void Tryte::set_trit(int i, const Trit& trit) {
        int shift = 2 * i;
        bct &= ~(1 << shift);
        bct |= trit.val << shift;
    } 

    std::string Tryte::to_ternary_str() const {
        std::string result;
        for(int i = TRYTE_TRIT - 1; i >= 0; i--) {
            result = result + get_trit(i).to_char();
        }
        return result;
    }
} // namespace termite
