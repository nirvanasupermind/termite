// -*- core/trybble.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "trybble.h"

namespace termite
{
    Trybble::Trybble(uint8_t bits)
        : bits(bits)
    {
    }

    Trybble::Trybble(int8_t val)
    {
        switch (val)
        {
        case -13:
            bits = 0b101010; // TTT
            break;
        case -12:
            bits = 0b101000; // TT0
            break;
        case -11:
            bits = 0b101001; // TT1
            break;
        case -10:
            bits = 0b100010; // T0T
            break;
        case -9:
            bits = 0b100000; // T00
            break;
        case -8:
            bits = 0b100001; // T01
            break;
        case -7:
            bits = 0b100110; // T1T
            break;
        case -6:
            bits = 0b100100; // T10
            break;
        case -5:
            bits = 0b100101; // T11
            break;
        case -4:
            bits = 0b001010; // 0TT
            break;
        case -3:
            bits = 0b001000; // 0T0
            break;
        case -2:
            bits = 0b001001; // 0T1
            break;
        case -1:
            bits = 0b000010; // 00T
            break;
        case 0:
            bits = 0b000000; // 000
            break;
        case 1:
            bits = 0b000001; // 001
            break;
        case 2:
            bits = 0b000110; // 01T
            break;
        case 3:
            bits = 0b000100; // 010
            break;
        case 4:
            bits = 0b000101; // 011
            break;
        case 5:
            bits = 0b011010; // 1TT
            break;
        case 6:
            bits = 0b011000; // 1T0
            break;
        case 7:
            bits = 0b011001; // 1T1
            break;
        case 8:
            bits = 0b010010; // 10T
            break;
        case 9:
            bits = 0b010000; // 100
            break;
        case 10:
            bits = 0b010001; // 101
            break;
        case 11:
            bits = 0b010110; // 11T
            break;
        case 12:
            bits = 0b010100; // 110
            break;
        case 13:
            bits = 0b010101; // 111
            break;
        default:
            bits = 0;
            break;
        }
    }

    int8_t Trybble::to_int8() const
    {
        switch (bits)
        {
        case 0b101010:
            return -13; // TTT
        case 0b101000:
            return -12; // TT0
        case 0b101001:
            return -11; // TT1
        case 0b100010:
            return -10; // T0T
        case 0b100000:
            return -9; // T00
        case 0b100001:
            return -8; // T01
        case 0b100110:
            return -7; // T1T
        case 0b100100:
            return -6; // T10
        case 0b100101:
            return -5; // T11
        case 0b001010:
            return -4; // 0TT
        case 0b001000:
            return -3; // 0T0
        case 0b001001:
            return -2; // 0T1
        case 0b000010:
            return -1; // 00T
        case 0b000000:
            return 0; // 000
        case 0b000001:
            return 1; // 001
        case 0b000110:
            return 2; // 01T
        case 0b000100:
            return 3; // 010
        case 0b000101:
            return 4; // 011
        case 0b011010:
            return 5; // 1TT
        case 0b011000:
            return 6; // 1T0
        case 0b011001:
            return 7; // 1T1
        case 0b010010:
            return 8; // 10T
        case 0b010000:
            return 9; // 100
        case 0b010001:
            return 10; // 101
        case 0b010110:
            return 11; // 11T
        case 0b010100:
            return 12; // 110
        case 0b010101:
            return 13; // 111
        default:
            return 0;
        }
    }

    std::string Trybble::to_ternary_str() const
    {
        switch (bits)
        {
        case 0b101010:
            return "TTT";
        case 0b101000:
            return "TT0";
        case 0b101001:
            return "TT1";
        case 0b100010:
            return "T0T";
        case 0b100000:
            return "T00";
        case 0b100001:
            return "T01";
        case 0b100110:
            return "T1T";
        case 0b100100:
            return "T10";
        case 0b100101:
            return "T11";
        case 0b001010:
            return "0TT";
        case 0b001000:
            return "0T0";
        case 0b001001:
            return "0T1";
        case 0b000010:
            return "00T";
        case 0b000000:
            return "000";
        case 0b000001:
            return "001";
        case 0b000110:
            return "01T";
        case 0b000100:
            return "010";
        case 0b000101:
            return "011";
        case 0b011010:
            return "1TT";
        case 0b011000:
            return "1T0";
        case 0b011001:
            return "1T1";
        case 0b010010:
            return "10T";
        case 0b010000:
            return "100";
        case 0b010001:
            return "101";
        case 0b010110:
            return "11T";
        case 0b010100:
            return "110";
        case 0b010101:
            return "111";
        default:
            return 0;
        }
    }

    uint8_t Trybble::first_trit() const
    {
        return ((bits & 32) << 1) + (bits & 16);
    }

    uint8_t Trybble::second_trit() const
    {
        return ((bits & 8) << 1) + (bits & 4);
    }

    uint8_t Trybble::third_trit() const
    {
        return ((bits & 2) << 1) + (bits & 1);
    }
} // namespace termite