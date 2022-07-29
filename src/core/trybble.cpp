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
        case 0:
            bits = 0b000000; // 000
            break;
        case 1:
            bits = 0b000001; // 001
            break;
        case 2:
            bits = 0b000010; // 002
        case 3:
            bits = 0b000100; // 010
        case 4:
            bits = 0b000101; // 011
        case 5:
            bits = 0b000110; // 012
        case 6:
            bits = 0b001000; // 020
        case 7:
            bits = 0b001001; // 021
        case 8:
            bits = 0b001010; // 022
        case 9:
            bits = 0b010000; // 100
        case 10:
            bits = 0b010001; // 101
        case 11:
            bits = 0b010010; // 102
        case 12:
            bits = 0b010100; // 110
        case 13:
            bits = 0b010101; // 111
        case 14:
            bits = 0b010110; // 112
        case 15:
            bits = 0b011000; // 120
        case 16:
            bits = 0b011001; // 121
        case 17:
            bits = 0b011010; // 122
        case 18:
            bits = 0b100000; // 200
        case 19:
            bits = 0b100001; // 201
        case 20:
            bits = 0b100010; // 202
        case 21:
            bits = 0b100100; // 210
        case 22:
            bits = 0b100101; // 211
        case 23:
            bits = 0b100110; // 212
        case 24:
            bits = 0b101000; // 220
        case 25:
            bits = 0b101001; // 221
        case 26:
            bits = 0b101010; // 222
        default:
            bits = 0;
            break;
        }
    }

    int8_t Trybble::to_int8() const
    {
        switch (bits)
        {
        case 0b000000:
            return 0; // 000
        case 0b000001:
            return 1; // 001
        case 0b000010:
            return 2; // 002
        case 0b000100:
            return 3; // 010
        case 0b000101:
            return 4; // 011
        case 0b000110:
            return 5; // 012
        case 0b001000:
            return 6; // 020
        case 0b001001:
            return 7; // 021
        case 0b001010: 
            return 8; // 022
        case 0b010000:
            return 9; // 100
        case 0b010001:
            return 10; // 101
        case 0b010010:
            return 11; // 102
        case 0b010100:
            return 12; // 110
        case 0b010101:
            return 13; // 111
        case 0b010110:
            return 14; // 112
        case 0b011000:
            return 15; // 120
        case 0b011001:
            return 16; // 121
        case 0b011010:
            return 17; // 122
        case 0b100000:
            return 18; // 200
        case 0b100001:
            return 19; // 201
        case 0b100010: 
            return 20; // 202
        case 0b100100:
            return 21; // 210
        case 0b100101:
            return 22; // 211
        case 0b100110:
            return 23; // 212
        case 0b101000:
            return 24; // 220
        case 0b101001:
            return 25; // 221
        case 0b101010:
            return 26; // 222
        default:
            return 0;
        }
    }

    std::string Trybble::to_ternary_str() const
    {
        switch (bits)
        {
        case 0b000000:
            return "000";
        case 0b000001:
            return "001";
        case 0b000010:
            return "002";
        case 0b000100:
            return "010";
        case 0b000101:
            return "011";
        case 0b000110:
            return "012";
        case 0b001000:
            return "020";
        case 0b001001:
            return "021";
        case 0b001010: 
            return "022";
        case 0b010000:
            return "100";
        case 0b010001:
            return "101";
        case 0b010010:
            return "102";
        case 0b010100:
            return "110";
        case 0b010101:
            return "111";
        case 0b010110:
            return "112";
        case 0b011000:
            return "120";
        case 0b011001:
            return "121";
        case 0b011010:
            return "122";
        case 0b100000:
            return "200";
        case 0b100001:
            return "201";
        case 0b100010: 
            return "202";
        case 0b100100:
            return "210";
        case 0b100101:
            return "211";
        case 0b100110:
            return "212";
        case 0b101000:
            return "220";
        case 0b101001:
            return "221";
        case 0b101010:
            return "222";
        default:
            return 0;
        }
    }

    char Trybble::to_hept_chr() const
    {
        switch (bits)
        {
        case 0b000000:
            return '0'; // 000
        case 0b000001:
            return '1'; // 001
        case 0b000010:
            return '2'; // 002
        case 0b000100:
            return '3'; // 010
        case 0b000101:
            return '4'; // 011
        case 0b000110:
            return '5'; // 012
        case 0b001000:
            return '6'; // 020
        case 0b001001:
            return '7'; // 021
        case 0b001010: 
            return '8'; // 022
        case 0b010000:
            return '9'; // 100
        case 0b010001:
            return 'a'; // 101
        case 0b010010:
            return 'b'; // 102
        case 0b010100:
            return 'c'; // 110
        case 0b010101:
            return 'd'; // 111
        case 0b010110:
            return 'e'; // 112
        case 0b011000:
            return 'f'; // 120
        case 0b011001:
            return 'g'; // 121
        case 0b011010:
            return 'h'; // 122
        case 0b100000:
            return 'i'; // 200
        case 0b100001:
            return 'j'; // 201
        case 0b100010: 
            return 'k'; // 202
        case 0b100100:
            return 'l'; // 210
        case 0b100101:
            return 'm'; // 211
        case 0b100110:
            return 'n'; // 212
        case 0b101000:
            return 'o'; // 220
        case 0b101001:
            return 'p'; // 221
        case 0b101010:
            return 'q'; // 222
        default:
            return '\0';
        }
    }
} // namespace termite