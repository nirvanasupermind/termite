#include <algorithm>

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

    Trit::Trit(char chr)
        : val(chr == 'Z' ? -1 : (chr == '0' ? 0 : 1))
    {
    }

    Trit Trit::clone() const
    {
        return Trit(val);
    }

    Trit Trit::operator&&(const Trit &other) const
    {
        return Trit(std::min(val, other.val));
    }

    Trit Trit::operator||(const Trit &other) const
    {
        return Trit(std::max(val, other.val));
    }

    Trit Trit::operator^(const Trit &other) const
    {
        return Trit((-val) * other.val);
    }

    bool Trit::operator==(const Trit &other) const
    {
        return val == other.val;
    }

    Trit Trit::operator!() const
    {
        return Trit(-val);
    }

    char Trit::to_chr() const
    {
        return (val == -1 ? 'Z' : (val == 0 ? '0' : '1'));
    }

    const Trit Trit::MINUS_ONE(-1);
    const Trit Trit::ZERO(0);
    const Trit Trit::ONE(1);
} // namespace termite