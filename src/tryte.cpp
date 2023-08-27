#include <cstdint>
#include "tryte.h"

namespace termite {
    // This is the BCT for number 0
    Tryte::Tryte()
        : bct(0b0101010101010101) {
    }

    Tryte::Tryte(uint16_t bct)
        : bct(bct) {
        
    }

    uint16_t Tryte::get_bct() const {
        return bct;
    }
    
    uint8_t Tryte::get_trit(int i) const {
        return (bct >> (2 * i)) & 3;
    }

} // namespace termite
