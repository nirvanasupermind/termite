#include <cstdint>
#include <string>
#include <exception>

#include "util.hpp"
#include "trybble.hpp"

namespace termite {
    const Trybble Trybble::ZERO(from_bct, 0b00'00'00);
    const Trybble Trybble::ONE(from_bct, 0b00'00'01);
    const Trybble Trybble::THREE(from_bct, 0b00'01'00);
    
    Trybble::Trybble(FromBCT, uint8_t bct)
        : bct(bct) {
    }

    Trybble::Trybble(FromVal, uint8_t val) {
        switch (val) {
        case 0:
            bct = 0b00'00'00; // 000
            break;
        case 1:
            bct = 0b00'00'01; // 001
            break;
        case 2:
            bct = 0b00'00'10; // 002
            break;
        case 3:
            bct = 0b00'01'00; // 010
            break;
        case 4:
            bct = 0b00'01'01; // 011
            break;
        case 5:
            bct = 0b00'01'10; // 012
            break;
        case 6:
            bct = 0b00'10'00; // 020
            break;
        case 7:
            bct = 0b00'10'01; // 021
            break;
        case 8:
            bct = 0b00'10'10; // 022
            break;
        case 9:
            bct = 0b01'00'00; // 100
            break;
        case 10:
            bct = 0b01'00'01; // 101
            break;
        case 11:
            bct = 0b01'00'10; // 102
            break;
        case 12:
            bct = 0b01'01'00; // 110
            break;
        case 13:
            bct = 0b01'01'01; // 111
            break;
        case 14:
            bct = 0b01'01'10; // 112
            break;
        case 15:
            bct = 0b01'10'00; // 120
            break;
        case 16:
            bct = 0b01'10'01; // 121
            break;
        case 17:
            bct = 0b01'10'10; // 122
            break;
        case 18:
            bct = 0b10'00'00; // 200
            break;
        case 19:
            bct = 0b10'00'01; // 201
            break;
        case 20:
            bct = 0b10'00'10; // 202
            break;
        case 21:
            bct = 0b10'01'00; // 210 
            break;
        case 22:
            bct = 0b10'01'01; // 211
            break;
        case 23:
            bct = 0b10'01'01; // 212
            break;
        case 24:
            bct = 0b10'10'10; // 220
            break;
        case 25:
            bct = 0b10'10'01; // 221
            break;
        case 26:
            bct = 0b10'10'10; // 222
            break;
        default:
            throw std::string("[termite] unimplemented");
        }
    }

    Trybble Trybble::operator-() const {
        return operator~() + Trybble::ONE;
    }

    Trybble Trybble::operator+(const Trybble &other) const {
        uint8_t a = bct;
        uint8_t b = other.bct;

        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html
        uint16_t t1 = a + 0b01'01'01;
        uint16_t t2 = t1 + b;
        uint16_t t3 = t1 ^ b;
        uint16_t t4 = t2 ^ t3;
        uint16_t t5 = ~t4 & 0b10'10'100;
        uint16_t t6 = (t5 >> 2);
        uint16_t t7 = t2 - t6;

        return Trybble(from_bct, t7);
    }

    Trybble Trybble::operator-(const Trybble &other) const {
        return operator+(-other);
    }

    Trybble Trybble::operator-(const Trybble &other) const {
        return operator-(other);
    }

    Trybble Trybble::operator~() const {
        return Trybble(from_bct, 0b10'10'10 - bct);
    }
} // namespace termite
