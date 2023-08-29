#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include "tryte.h"

namespace termite {
    // This is the binary-coded ternary representation of 0
    Tryte::Tryte()
        : bct(0x5555) {
    }

    Tryte::Tryte(uint16_t bct)
        : bct(bct) {

    }

    uint16_t Tryte::get_bct() const {
        return bct;
    }

    uint8_t Tryte::get_bct_trit(int i) const {
        return (bct >> (2 * i)) & 3;
    }

    void Tryte::set_bct_trit(int i, uint8_t val) {
        bct = bct & ~(1 << (2 * i));
        bct = bct | (val << (2 * i));
    }

    std::string Tryte::str() const {
        std::string result = "";
        for (int i = 0; i < TRITS_PER_TRYTE; i++) {
            switch (get_bct_trit(i)) {
            case 0b00:
                result = std::string("T") + result;
                break;
            case 0b01:
                result = std::string("0") + result;
                break;
            case 0b10:
                result = std::string("1") + result;
                break;
            default:
                result = std::string("?") + result;
                break;
            }
        }
        return result;
    }
} // namespace termite 