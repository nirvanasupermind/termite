#include <iostream>
#include <string>
#include <array>
#include <cmath>

#include "trit.h"
#include "trybble.h"

namespace termite
{
    Trybble::Trybble(const std::array<Trit, 3> &trits)
        : trits(trits)
    {
    }

    Trybble Trybble::clone() const
    {
        std::array<Trit, 3> clonedTrits = trits;
        return Trybble(clonedTrits);
    }
    
    int Trybble::to_int() const
    {
        return trits.at(0).val * 9 + trits.at(1).val * 3 + trits.at(2).val;
    }
    
    char Trybble::to_chr() const
    {   
       switch(to_int())
       {
        case -13: return 'N';
        case -12: return 'O';
        case -11: return 'P';
        case -10: return 'Q';
        case -9: return 'R';
        case -8: return 'S';
        case -7: return 'T';
        case -6: return 'U';
        case -5: return 'V';
        case -4: return 'W';
        case -3: return 'X';
        case -2: return 'Y';
        case -1: return 'Z';
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        default: return '\0';
       }
    }

    
} // namespace termite