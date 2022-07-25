// -*- core/tryte.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "trybble.h"
#include "tryte.h"

namespace termite
{
    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : hi(hi), lo(lo)
    {
    }

    Trybble Tryte::hi_bct() const
    {
        return hi;
    }

    Trybble Tryte::lo_bct() const
    {
        return lo;
    }

    int8_t Tryte::hi_val() const
    {
        return hi.to_int8();
    }

    int8_t Tryte::lo_val() const
    {
        return lo.to_int8();
    }

    uint8_t Tryte::add_bct_trits(uint8_t a, uint8_t b)
    {
        if (a == 2)
        {
            switch (b)
            {
            case 0:
                return 2;
            case 1:
                return 0;
            case 2:
                return 1;
            default:
                return 0;
            }
        }

        if (b == 2)
        {
            return Tryte::add_bct_trits(b, a);
        }

        return (a + b) % 3;
    }

    Tryte Tryte::operator+(const Tryte &other) const
    {
        std::array<uint8_t, 6> a{hi.first_trit(), hi.second_trit(), hi.third_trit(), lo.first_trit(), lo.second_trit(), lo.third_trit()};
        std::array<uint8_t, 6> b{other.hi.first_trit(), other.hi.second_trit(), other.hi.third_trit(), other.lo.first_trit(), other.lo.second_trit(), other.lo.third_trit()};
        std::array<uint8_t, 6> result;
        uint8_t carry;

        for (size_t i = 0; i < 6; i++)
        {
            uint8_t a_trit = a.at(i);
            uint8_t b_trit = b.at(i);

            result.at(i) = (a_trit + b_trit + carry) % 3;
            carry = (a_trit + b_trit) / 3;
        }

        Trybble result_hi{(int8_t)((result.at(0) >> 2) + (result.at(1) >> 1) + result.at(2))};
        Trybble result_lo{(int8_t)((result.at(3) >> 2) + (result.at(4) >> 1) + result.at(5))};
        return Tryte(result_hi, result_lo);
    }

} // namespace termite