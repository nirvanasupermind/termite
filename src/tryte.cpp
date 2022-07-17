#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <functional>

#include "trit.h"
#include "duet.h"
#include "tryte.h"

namespace termite
{
    // int Tryte::mod3(int val)
    // {
    // 	if(val > 0)
    //     {
    // 		return val % 3;
    //     }

    //     val = val % 3;

    // 	return (val + 3) % 3;
    // }

    Tryte::Tryte(const std::array<Trit, 6> &trits)
        : trits(trits)
    {
    }

    Tryte::Tryte(const std::string &str)
    {
        for (int i = 2; i >= 0; i--)
        {
            Duet duet(str.at(i));
            trits[2 * i] = duet.hi;
            trits[2 * i + 1] = duet.lo;
        }
    }

    Tryte Tryte::clone() const
    {
        std::array<Trit, 6> clonedTrits = trits;
        return Tryte(clonedTrits);
    }

    Tryte Tryte::operator-() const
    {
        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            result.trits[i] = !(trits.at(i));
        }

        return result;
    }

    Tryte Tryte::operator+(const Tryte &other) const
    {
        Tryte result;

        Trit carry = Trit::ZERO;

        for (int i = 5; i >= 0; i--)
        {
            int sum = trits.at(i).val + other.trits.at(i).val + carry.val;

            if (sum == 2)
            {
                result.trits[i] = -1;
                carry = 1;
            }
            else if (sum == -2)
            {
                result.trits[i] = 1;
                carry = -1;
            }
            else
            {
                result.trits[i] = sum % 3;
                carry = sum / 3;
            }
        }

        return result;
    }

    Tryte Tryte::operator-(const Tryte &other) const
    {
        return operator+(-other);
    }

    Tryte Tryte::operator*(const Tryte &other) const
    {
        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            if (other.trits.at(i).val == -1)
            {
                result = result - operator<<(5 - i);
            }
            else if (other.trits.at(i).val == 1)
            {
                result = result + operator<<(5 - i);
            }
        }

        return result;
    }

    Tryte Tryte::operator<<(int amount) const
    {
        Tryte result;

        for (int i = 5 - amount; i >= 0; i--)
        {
            result.trits[i] = trits.at(i + amount);
        }

        return result;
    }

    Tryte Tryte::operator>>(int amount) const
    {
        // 64 >> 3 (binary) = 00100000 = 0001000 = 8
        // 64 >> 3 (ternary) = 001T11 = 000001T = 2

        Tryte result = clone();

        for (int i = 0; i < amount; i++)
        {
            std::copy_backward(std::begin(result.trits), std::end(result.trits) - 1, std::begin(result.trits) + 1);
            result.trits[0] = Trit::ZERO;
        }

        return result;
    }

    Trit Tryte::cmp(const Tryte &other) const
    {
        for (int i = 5; i >= 0; i--)
        {
            int a = trits.at(i).val;
            int b = other.trits.at(i).val;

            if (a < b)
            {
                return Trit::MINUS_ONE;
            }
            else if (a > b)
            {
                return Trit::ONE;
            }
        }

        return Trit::ZERO;
    }

    Tryte Tryte::operator&(const Tryte &other) const
    {
        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            result.trits[i] = trits.at(i) && other.trits.at(i);
        }

        return result;
    }

    Tryte Tryte::operator|(const Tryte &other) const
    {
        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            result.trits[i] = trits.at(i) || other.trits.at(i);
        }

        return result;
    }

    Tryte Tryte::operator^(const Tryte &other) const
    {
        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            result.trits[i] = trits.at(i) ^ other.trits.at(i);
        }

        return result;
    }

    Duet Tryte::hi_duet() const
    {
        return Duet(trits.at(0), trits.at(1));
    }

    Duet Tryte::mid_duet() const
    {
        return Duet(trits.at(2), trits.at(3));
    }

    Duet Tryte::lo_duet() const
    {
        return Duet(trits.at(4), trits.at(5));
    }

    int Tryte::to_int() const
    {
        return trits.at(0).val * 243 + trits.at(1).val * 81 + trits.at(2).val * 27 + trits.at(3).val * 9 + trits.at(4).val * 3 + trits.at(5).val;
    }

    std::string Tryte::to_str() const
    {
        return std::string() + hi_duet().to_chr() + mid_duet().to_chr() + lo_duet().to_chr();
    }

    const Tryte Tryte::MINUS_ONE("00Z");
    const Tryte Tryte::ZERO;
    const Tryte Tryte::ONE("001");

    size_t Tryte::HashFunction::operator()(const Tryte &tryte) const
    {
        return std::hash<int>()(tryte.to_int());
    }
} // namespace termite