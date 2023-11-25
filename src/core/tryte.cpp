#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include "tryte.h"
#include "tables.h"

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
        bct = bct & ~(0b11 << (2 * i));
        bct = bct | (val << (2 * i));
    }

    Tryte Tryte::operator~() const {
        Tryte result;
        for (int i = 0; i < TRITS_PER_TRYTE; i++) {
            result.set_bct_trit(i, TRIT_NOT[get_bct_trit(i)]);
        }
        return result;
    }

    int16_t Tryte::to_int16() const {
        int32_t result = 0;
        for (int i = 0; i < TRITS_PER_TRYTE; i++) {
            result += POW3[i] * ((int)(get_bct_trit(i) - 1));
        }
        return result;
    }

    std::string Tryte::to_ternary_str() const {
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

    wchar_t Tryte::to_wchar() const {
        return (wchar_t)(to_int16());
    }
    
    Tryte Tryte::from_int16(int16_t n) {
        if (n < 0) {
            return ~Tryte::from_int16(-n);
        }
        Tryte result;
        int i = 0;
        while (n > 0) {
            int rem = n % 3;
            n = n / 3;
            if (rem == 2) {
                rem = -1;
                n++;
            }
            result.set_bct_trit(i, rem + 1);
            i++;
        }
        return result;
    }


    Tryte Tryte::from_wchar(wchar_t wc) {
        return Tryte::from_int16((int16_t)(wc));
    }
} // namespace termite 