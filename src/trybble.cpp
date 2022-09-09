#include <cstdint>
#include <string>
#include <exception>
#include <algorithm>

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

        uint8_t a1 = ((bct >> 4) & 3), b1 = (other.bct >> 2) & 3;
        uint8_t a2 = ((bct >> 2) & 3), b2 = ((other.bct >> 2) & 3);
        uint8_t a3 = (bct & 3), b3 = (other.bct & 3);

        return Trybble(from_bct, std::min(a1, b1) >> 4 + std::min(a2, b2) >> 2 + std::min(a3, b3));
    }

    Trybble Trybble::operator|(const Trybble& other) const {
        uint8_t a = bct;
        uint8_t b = other.bct;

        uint8_t a1 = ((bct >> 4) & 3), b1 = (other.bct >> 2) & 3;
        uint8_t a2 = ((bct >> 2) & 3), b2 = ((other.bct >> 2) & 3);
        uint8_t a3 = (bct & 3), b3 = (other.bct & 3);

        return Trybble(from_bct, std::max(a1, b1) >> 4 + std::max(a2, b2) >> 2 + std::max(a3, b3));
    }

    Trybble Trybble::operator^(const Trybble& other) const {
        uint8_t a = bct;
        uint8_t b = other.bct;

        uint8_t a1 = ((bct >> 4) & 3), b1 = (other.bct >> 2) & 3;
        uint8_t a2 = ((bct >> 2) & 3), b2 = ((other.bct >> 2) & 3);
        uint8_t a3 = (bct & 3), b3 = (other.bct & 3);

        return Trybble(from_bct, ((a1 * -b1) + a1 + b1) >> 4 + ((a2 * -b2) + a2 + b2) >> 2 + ((a3 * -b3) + a3 + b3));
    }

    int8_t Trybble::to_int8_t() const {
        switch (bct) {
        case 0b00'00'00:
            return -13; // ZZZ
        case 0b00'00'01:
            return -12; // ZZ0
        case 0b00'00'10:
            return -11; // ZZ1
        case 0b00'01'00:
            return -10; // Z0Z
        case 0b00'01'01:
            return -9; // Z00
        case 0b00'01'10:
            return -8; // Z01
        case 0b00'10'00:
            return -7; // Z10
        case 0b00'10'01:
            return -6; // Z11
        case 0b00'10'10:
            return -5; // Z12
        case 0b01'00'00:
            return -4; // 0ZZ
        case 0b01'00'01:
            return -3; // 0Z0
        case 0b01'00'10:
            return -2; // 0Z1
        case 0b01'01'00:
            return -1; // 00Z
        case 0b01'01'01:
            return 0; // 000
        case 0b01'01'10:
            return 1; // 001
        case 0b01'10'00:
            return 2; // 01Z
        case 0b01'10'01:
            return 3; // 010
        case 0b01'10'10:
            return 4; // 011
        case 0b10'00'00:
            return 5; // 1ZZ
        case 0b10'00'01:
            return 6; // 1Z0
        case 0b10'00'10:
            return 7; // 1Z1
        case 0b10'01'00:
            return 8; // 10Z 
        case 0b10'01'01:
            return 9; // 100
        case 0b10'01'10:
            return 10; // 101
        case 0b10'10'00:
            return 11; // 11Z
        case 0b10'10'01:
            return 12; // 110
        case 0b10'10'10:
            return 13; // 111
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }

    std::string Trybble::to_ternary_str() const {
        switch (bct) {
        case 0b00'00'00:
            return "ZZZ";
        case 0b00'00'01:
            return "ZZ0";
        case 0b00'00'10:
            return "ZZ1";
        case 0b00'01'00:
            return "Z0Z";
        case 0b00'01'01:
            return "Z00";
        case 0b00'01'10:
            return "Z01";
        case 0b00'10'00:
            return "Z1Z";
        case 0b00'10'01:
            return "Z10";
        case 0b00'10'10:
            return "Z11";
        case 0b01'00'00:
            return "0ZZ";
        case 0b01'00'01:
            return "0Z0";
        case 0b01'00'10:
            return "0Z1";
        case 0b01'01'00:
            return "00Z";
        case 0b01'01'01:
            return "000";
        case 0b01'01'10:
            return "001";
        case 0b01'10'00:
            return "01Z";
        case 0b01'10'01:
            return "010";
        case 0b01'10'10:
            return "011";
        case 0b10'00'00:
            return "1ZZ";
        case 0b10'00'01:
            return "1Z0";
        case 0b10'00'10:
            return "1Z1";
        case 0b10'01'00:
            return "10Z";
        case 0b10'01'01:
            return "100";
        case 0b10'01'10:
            return "101";
        case 0b10'10'00:
            return "11Z";
        case 0b10'10'01:
            return "110";
        case 0b10'10'10:
            return "111";
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }

    char Trybble::to_hept_digit() const {
        switch (bct) {
        case 0b00'00'00:
            return 'N';
        case 0b00'00'01:
            return 'O';
        case 0b00'00'10:
            return 'P';
        case 0b00'01'00:
            return 'Q';
        case 0b00'01'01:
            return 'R';
        case 0b00'01'10:
            return 'S';
        case 0b00'10'00:
            return 'T';
        case 0b00'10'01:
            return 'U';
        case 0b00'10'10:
            return 'V';
        case 0b01'00'00:
            return 'W';
        case 0b01'00'01:
            return 'X';
        case 0b01'00'10:
            return 'Y';
        case 0b01'01'00:
            return 'Z';
        case 0b01'01'01:
            return '0';
        case 0b01'01'10:
            return '1';
        case 0b01'10'00:
            return '2';
        case 0b01'10'01:
            return '3';
        case 0b01'10'10:
            return '4';
        case 0b10'00'00:
            return '5';
        case 0b10'00'01:
            return '6';
        case 0b10'00'10:
            return '7';
        case 0b10'01'00:
            return '8';
        case 0b10'01'01:
            return '9';
        case 0b10'01'10:
            return 'A';
        case 0b10'10'00:
            return 'B';
        case 0b10'10'01:
            return 'C';
        case 0b10'10'10:
            return 'D';
        default:
            throw std::runtime_error("[termite] unimplemented");
        }
    }

    bool Trybble::is_neg() const {
        return bct < 0b01'01'01;
    }
} // namespace termite