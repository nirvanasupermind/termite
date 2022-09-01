#include <cstdint>
#include <string>

#include "util.hpp"
#include "trybble.hpp"

namespace termite {
    Trybble::Trybble(FromBCT, uint8_t bct)
        : bct(bct) {
    }

    Trybble::Trybble(FromVal, uint8_t val) {
        switch (val) {
        case 0:
            bct = B(00, 00, 00); // 000
            break;
        case 1:
            bct = B(00, 00, 01); // 001
            break;
        case 2:
            bct = B(00, 00, 10); // 002
            break;
        case 3:
            bct = B(00, 01, 00); // 010
            break;
        case 4:
            bct = B(00, 01, 01); // 011
            break;
        case 5:
            bct = B(00, 01, 10); // 012
            break;
        case 6:
            bct = B(00, 10, 00); // 020
            break;
        case 7:
            bct = B(00, 10, 01); // 021
            break;
        case 8:
            bct = B(00, 10, 10); // 022
            break;
        case 9:
            bct = B(01, 00, 00); // 100
            break;
        case 10:
            bct = B(01, 00, 01); // 101
            break;
        case 11:
            bct = B(01, 00, 10); // 102
            break;
        case 12:
            bct = B(01, 01, 00); // 110
            break;
        case 13:
            bct = B(01, 01, 01); // 111
            break;
        case 14:
            bct = B(01, 01, 10); // 112
            break;
        case 15:
            bct = B(01, 10, 00); // 120
            break;
        case 16:
            bct = B(01, 10, 01); // 121
            break;
        case 17:
            bct = B(01, 10, 10); // 122
            break;
        case 18:
            bct = B(10, 00, 00); // 200
            break;
        case 19:
            bct = B(10, 00, 01); // 201
            break;
        case 20:
            bct = B(10, 00, 10); // 201
            break;
        }
    }
} // namespace termite
