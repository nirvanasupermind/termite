#include "trit.h"
#include "trybble.h"

namespace termite
{
    Trybble::Trybble()
        : trit0(Trit::ZERO), trit1(Trit::ZERO), trit2(Trit::ZERO)
    {
    }

    Trybble::Trybble(const Trit &trit0, const Trit &trit1, const Trit &trit2)
        : trit0(trit0), trit1(trit1), trit2(trit2)
    {
    }

    Trybble::Trybble(char chr)
    {
        switch (chr)
        {
        case 'L':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'M':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ZERO;
            break;
        case 'N':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ONE;
            break;
        case 'O':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'P':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::ZERO;
            break;
        case 'Q':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'R':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::ZERO;
            break;
        case 'S':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::ONE;
            break;
        case 'T':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'U':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::ZERO;
            break;
        case 'V':
            trit0 = Trit::MINUS_ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::ONE;
            break;
        case 'W':
            trit0 = Trit::ZERO;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'X':
            trit0 = Trit::ZERO;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ZERO;
            break;
        case 'Y':
            trit0 = Trit::ZERO;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ONE;
            break;
        case 'Z':
            trit0 = Trit::ZERO;
            trit1 = Trit::ZERO;
            trit2 = Trit::MINUS_ONE;
            break;
        case '0':
            trit0 = Trit::ZERO;
            trit1 = Trit::ZERO;
            trit2 = Trit::ZERO;
            break;
        case '1':
            trit0 = Trit::ZERO;
            trit1 = Trit::ZERO;
            trit2 = Trit::ONE;
            break;
        case '2':
            trit0 = Trit::ZERO;
            trit1 = Trit::ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case '3':
            trit0 = Trit::ZERO;
            trit1 = Trit::ONE;
            trit2 = Trit::ZERO;
            break;
        case '4':
            trit0 = Trit::ZERO;
            trit1 = Trit::ONE;
            trit2 = Trit::ONE;
            break;
        case '5':
            trit0 = Trit::ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case '6':
            trit0 = Trit::ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ZERO;
            break;
        case '7':
            trit0 = Trit::ONE;
            trit1 = Trit::MINUS_ONE;
            trit2 = Trit::ONE;
            break;
        case '8':
            trit0 = Trit::ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::MINUS_ONE;
            break;
        case '9':
            trit0 = Trit::ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::ZERO;
            break;
        case 'A':
            trit0 = Trit::ONE;
            trit1 = Trit::ZERO;
            trit2 = Trit::ONE;
            break;
        case 'B':
            trit0 = Trit::ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::MINUS_ONE;
            break;
        case 'C':
            trit0 = Trit::ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::ZERO;
            break;
        default:
            trit0 = Trit::ONE;
            trit1 = Trit::ONE;
            trit2 = Trit::ONE;
            break;
        }
    }

    Trybble Trybble::clone() const
    {
        return Trybble(trit0.clone(), trit1.clone(), trit2.clone());
    }

    int Trybble::to_int() const
    {
        return trit0.val * 9 + trit1.val * 2 + trit2.val;
    }

    char Trybble::to_chr() const
    {
        switch (to_int())
        {
        case -13:
            return 'L';
        case -12:
            return 'M';
        case -11:
            return 'M';
        case -10:
            return 'O';
        case -4:
            return 'W';
        case -3:
            return 'X';
        case -2:
            return 'Y';
        case -1:
            return 'Z';
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        }
    }
} // namespace termite