//-*- core/translate.cpp -*-/
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "trybble.h"
#include "translate.h"

namespace termite
{
    int8_t trybble_to_int8(Trybble trybble)
    {
        switch (trybble)
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

    Trybble int8_to_trybble(int8_t val)
    {
        switch (val)
        {
        case -13:
            return 0b101010; // TTT
        case -12:
            return 0b101000; // TT0
        case -11:
            return 0b101001; // TT1
        case -10:
            return 0b100010; // T0T
        case -9:
            return 0b100000; // T00
        case -8:
            return 0b100001; // T01f
        case -7:
            return 0b100110; // T1T
        case -6:
            return 0b100100; // T10
        case -5:
            return 0b100101; // T11
        case -4:
            return 0b001010; // 0TT
        case -3:
            return 0b001000; // 0T0
        case -2:
            return 0b001001; // 0T1
        case -1:
            return 0b000010; // 00T
        case 0:
            return 0b000000; // 000
        case 1:
            return 0b000001; // 001
        case 2:
            return 0b000110; // 01T
        case 3:
            return 0b000100; // 010
        case 4:
            return 0b000101; // 011
        case 5:
            return 0b011010; // 1TT
        case 6:
            return 0b011000; // 1T0
        case 7:
            return 0b011001; // 1T1
        case 8:
            return 0b010010; // 10T
        case 9:
            return 0b010000; // 100
        case 10:
            return 0b010001; // 101
        case 11:
            return 0b010110; // 11T
        case 12:
            return 0b010100; // 110
        case 13:
            return 0b010101; // 111
        default:
            return 0;
        }
    }

    std::string trybble_to_ternary_str(Trybble trybble)
    {
        switch (trybble)
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
            return "";
        }
    }

} // namespace termite