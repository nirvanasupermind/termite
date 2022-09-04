#include <cstdint>
#include <string>
#include <exception>

#include "util.hpp"
#include "trybble.hpp"

namespace termite {
    const Trybble Trybble::MINUS_ONE(from_bct, 0b00'00'00);
    const Trybble Trybble::ZERO(from_bct, 0b00'00'01);
    const Trybble Trybble::ONE(from_bct, 0b00'00'10);

    Trybble::Trybble(FromBCT, uint8_t bct)
        : bct(bct) {
    }

    Trybble::Trybble(FromVal, int8_t val) {
        switch (val) {
        case -13:
            bct = 0b00'00'00; // ZZZ
            break;
        case -12:
            bct = 0b00'00'01; // ZZ0
            break;
        case -11:
            bct = 0b00'00'10; // ZZ1
            break;
        case -10:
            bct = 0b00'01'00; // Z0Z
            break;
        case -9:
            bct = 0b00'01'01; // Z00
            break;
        case -8:
            bct = 0b00'01'10; // Z01
            break;
        case -7:
            bct = 0b00'10'00; // Z1Z
            break;
        case -6:
            bct = 0b00'10'01; // Z10
            break;
        case -5:
            bct = 0b00'10'10; // Z11
            break;
        case -4:
            bct = 0b01'00'00; // 0ZZ
            break;
        case -3:
            bct = 0b01'00'01; // 0Z0
            break;
        case -2:
            bct = 0b01'00'10; // 0Z1
            break;
        case -1:
            bct = 0b01'01'00; // 00Z
            break;
        case 0:
            bct = 0b01'01'01; // 000
            break;
        case 1:
            bct = 0b01'01'10; // 001
            break;
        case 2:
            bct = 0b01'10'00; // 01Z
            break;
        case 3:
            bct = 0b01'10'01; // 010
            break;
        case 4:
            bct = 0b01'10'10; // 011
            break;
        case 5:
            bct = 0b10'00'00; // 1ZZ
            break;
        case 6:
            bct = 0b10'00'01; // 1Z0
            break;
        case 7:
            bct = 0b10'00'10; // 1Z1
            break;
        case 8:
            bct = 0b10'01'00; // 10Z 
            break;
        case 9:
            bct = 0b10'01'01; // 100
            break;
        case 10:
            bct = 0b10'01'10; // 101
            break;
        case 11:
            bct = 0b10'10'00; // 11Z
            break;
        case 12:
            bct = 0b10'10'01; // 110
            break;
        case 13:
            bct = 0b10'10'10; // 111
            break;
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }

    Trybble Trybble::operator-() const {
        return operator~();
    }

    Trybble Trybble::operator+(const Trybble& other) const {
        uint8_t a = bct;
        uint8_t b = other.bct;

        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html
        uint8_t t1 = a + 0b01'01'01;
        uint8_t t2 = t1 + b;
        uint8_t t3 = t1 ^ b;
        uint8_t t4 = t2 ^ t3;
        uint8_t t5 = ~t4 & 0b10'10'100;
        uint8_t t6 = (t5 >> 2);
        uint8_t t7 = 0b10'10'10 - (t2 - t6);

        return Trybble(from_bct, t7);
    }

    Trybble Trybble::operator-(const Trybble& other) const {
        return operator+(-other);
    }

    Trybble Trybble::operator*(const Trybble& other) const {
        return Trybble(from_val, (to_int8_t() * other.to_int8_t()) % 27);        
    }

    Trybble Trybble::operator/(const Trybble& other) const {
        if (is_neg() ^ other.is_neg()) {
            return -udiv(other);
        }

        return udiv(other);
    }

    Trybble Trybble::udiv(const Trybble& other) const {
        return Trybble(from_val, to_int8_t() / other.to_int8_t());
    }

    Trybble Trybble::operator~() const {
        return Trybble(from_bct, 0b10'10'10 - bct);
    }

    Trybble Trybble::operator&(const Trybble& other) const {
        uint8_t a = bct;
        uint8_t b = other.bct;

        // 00 & n = 00
        // 10 & n = n

        // n & 211 = 

        uint16_t t1 = a ^ 0b00'01'00

        return Trybble(from_bct, t7);
    }

    bool Trybble::is_neg() const {
        return bct >= 0b01'01'01;
    }

    int8_t Trybble::to_int8_t() const {
        switch (bct) {
        case 0b00'00'00:
            return -13; // ZZZ
        case 0b00'00'01:
            return -12; // ZZ0
        case 0b00'00'10:
            return -11; // ZZ1
        case 0b00'01'00: // 010
            return 3;
        case 0b00'01'01:
            return 4; // 011
        case 0b00'01'10:
            return 5; // 012
        case 0b00'10'00:
            return 6; // 020
        case 0b00'10'01:
            return 7; // 021
        case 0b00'10'10:
            return 8; // 022
        case 0b01'00'00:
            return 9; // 100
        case 0b01'00'01:
            return 10; // 101
        case 0b01'00'10:
            return 11; // 102
        case 0b01'01'00:
            return 12; // 110
        case 0b01'01'01:
            return 13; // 111
        case 0b01'01'10:
            return 14; // 112
        case 0b01'10'00:
            return 15; // 120
        case 0b01'10'01:
            return 16; // 121
        case 0b01'10'10:
            return 17; // 122
        case 0b10'00'00:
            return 18; // 200
        case 0b10'00'01:
            return 19; // 201
        case 0b10'00'10:
            return 20; // 202
        case 0b10'01'00:
            return 21; // 210 
        case 0b10'01'01:
            return 22; // 211
        case 0b10'01'10:
            return 23; // 212
        case 0b10'10'00:
            return 24; // 220
        case 0b10'10'01:
            return 25; // 221
        case 0b10'10'10:
            return 26; // 222
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }

    std::string Trybble::to_ternary_str() const {
        switch (bct) {
        case 0b00'00'00:
            return "000";
        case 0b00'00'01:
            return "001";
        case 0b00'00'10:
            return "002";
        case 0b00'01'00:
            return "010";
        case 0b00'01'01:
            return "011";
        case 0b00'01'10:
            return "012";
        case 0b00'10'00:
            return "020";
        case 0b00'10'01:
            return "021";
        case 0b00'10'10:
            return "022";
        case 0b01'00'00:
            return "100";
        case 0b01'00'01:
            return "101";
        case 0b01'00'10:
            return "102";
        case 0b01'01'00:
            return "110";
        case 0b01'01'01:
            return "111";
        case 0b01'01'10:
            return "112";
        case 0b01'10'00:
            return "120";
        case 0b01'10'01:
            return "121";
        case 0b01'10'10:
            return "122";
        case 0b10'00'00:
            return "200";
        case 0b10'00'01:
            return "201";
        case 0b10'00'10:
            return "202";
        case 0b10'01'00:
            return "210";
        case 0b10'01'01:
            return "211";
        case 0b10'01'10:
            return "212";
        case 0b10'10'00:
            return "220";
        case 0b10'10'01:
            return "221";
        case 0b10'10'10:
            return "222";
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }
} // namespace termite