#include <cinttypes>
#include <string>
#include "trit.h"
#include "tryte.h"

namespace termite {
    Word Word::from_int16(int16_t n) {
        if(n < 0) {
            // Use three's complement for negative numbers
            // https://homepage.cs.uiowa.edu/~dwjones/ternary/numbers.shtml
            return Word::from_int16(TRYTE_MAX + n);
        }

        Word result;
        for(int i = 0; i < TRYTE_TRIT; i++) {
            int r = n % 3;
            result.set_trit(i, Trit(r));
            n /= 3;
        }
        return result;
    }

    Word::Word() 
        : bct(0) {


    }
    Word::Word(uint16_t bct) 
        : bct(bct) {

    }

    Word Word::operator-() const {
        Word result;
        for(int i = 0; i < TRYTE_TRIT; i++) {
            result.set_trit(i, ~get_trit(i));
        }
        return result;
    }


    int16_t Word::to_int16() const {
        int16_t result = 0;
        for (int i = 0; i < TRYTE_TRIT; i++) {
            result = result + POW3[i] * get_trit(i).val;
        }
        return result;
    }

    Trit Word::get_trit(int i) const {
        return Trit((bct >> (2 * i) & 0b11));
    }
    
    void Word::set_trit(int i, const Trit& trit) {
        int shift = 2 * i;
        bct &= ~(1 << shift);
        bct |= trit.val << shift;
    } 

    std::string Word::to_ternary_str() const {
        std::string result;
        for(int i = TRYTE_TRIT - 1; i >= 0; i--) {
            result = result + get_trit(i).to_char();
        }
        return result;
    }
} // namespace termite
