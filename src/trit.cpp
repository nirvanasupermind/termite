#include "trit.h"

namespace termite
{
    Trit::Trit()
        : val(0)
    {
    }

    Trit::Trit(int val)
        : val(val)
    {
    }

    Trit Trit::operator!() const
    {
        return -val;
    }

    Trit Trit::operator&&(const Trit &b) const
    {
        return (val < b.val) ? val : b.val;
    }

    Trit Trit::operator||(const Trit &b) const
    {
        return (val > b.val) ? val : b.val;
    }

    Trit Trit::operator^(const Trit &b) const
    {
        return operator&&(!b) || (b && (operator!()));
    }
    
    bool Trit::operator==(const Trit &b) const
    {
        return val == b.val;
    }

    bool Trit::operator!=(const Trit &b) const
    {
        return val != b.val;
    }

    char Trit::charVal() const
    {
        switch(val)
        {
            case -1:
                return 'T';
            case 0:
                return '0';
            default:
                return '1';
        }
    }

    Trit Trit::fromChar(char chr)
    {
        switch(chr)
        {
            case 'T':
                return Trit::NEG;
            case '0':
                return Trit::ZERO;
            default:
                return Trit::ONE;
        }
    }

    const Trit Trit::ZERO(0);
    const Trit Trit::ONE(1);
    const Trit Trit::NEG(-1);
}