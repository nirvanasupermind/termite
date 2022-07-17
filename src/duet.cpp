#include "trit.h"
#include "duet.h"

namespace termite
{
    Duet::Duet()
        : hi(Trit::ZERO), lo(Trit::ZERO)
    {
    }

    Duet::Duet(const Trit &hi, const Trit &lo)
        : hi(hi), lo(lo)
    {
    }

    Duet::Duet(char chr)
    {
        switch (chr)
        {
        case 'W':
            hi = Trit::MINUS_ONE;
            lo = Trit::MINUS_ONE;
            break;
        case 'X':
            hi = Trit::MINUS_ONE;
            lo = Trit::ZERO;
            break;
        case 'Y':
            hi = Trit::MINUS_ONE;
            lo = Trit::ONE;
            break;
        case 'Z':
            hi = Trit::ZERO;
            lo = Trit::MINUS_ONE;
            break;
        case '0':
            hi = Trit::ZERO;
            lo = Trit::ZERO;
            break;
        case '1':
            hi = Trit::ZERO;
            lo = Trit::ONE;
            break;
        case '2':
            hi = Trit::ONE;
            lo = Trit::MINUS_ONE;
            break;
        case '3':
            hi = Trit::ONE;
            lo = Trit::ZERO;
            break;
        default:
            hi = Trit::ONE;
            lo = Trit::ONE;
            break;
        }
    }

    Duet Duet::clone() const
    {
        return Duet(hi.clone(), lo.clone());
    }

    int Duet::to_int() const
    {
        return hi.val * 3 + lo.val;
    }

    char Duet::to_chr() const
    {
        switch (to_int())
        {
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
        default:
            return '4';
        }
    }
} // namespace termite