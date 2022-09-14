#include <cinttypes>
#include <string>

#include "util.hpp"
#include "trit.hpp"

namespace termite {
    const Trit Trit::MINUS(from_bct, 0b00), Trit::ZERO(from_bct, 0b01), Trit::ONE(from_bct, 0b10);

    Trit::Trit(FromBCT, uint8_t bct)
        : bct(bct) {
    }

    Trit::Trit(FromVal, int8_t val)
        : bct((val == -1 ? 0b00 :
            (val == 0 ? 0b01 : 0b10))) {
    }
} // namespace termite