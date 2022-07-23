#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <functional>

#include "trit.h"
#include "trybble.h"
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

    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
    {
        trits[0] = hi.trit0;
        trits[1] = hi.trit1;
        trits[2] = hi.trit2;
        trits[3] = lo.trit0;
        trits[4] = lo.trit1;
        trits[5] = lo.trit2;
    }

    Tryte::Tryte(const std::string &str)
    {
        Trybble hi = Trybble(str.at(0));
        Trybble lo = Trybble(str.at(1));

        trits[0] = hi.trit0;
        trits[1] = hi.trit1;
        trits[2] = hi.trit2;
        trits[3] = lo.trit0;
        trits[4] = lo.trit1;
        trits[5] = lo.trit2;
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

    Trybble Tryte::hi_trybble() const
    {
        return Trybble(trits.at(0), trits.at(1), trits.at(2));
    }

    Trybble Tryte::lo_trybble() const
    {
        return Trybble(trits.at(3), trits.at(4), trits.at(5));
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

    bool Tryte::operator==(const Tryte &other) const
    {
        return to_int() == other.to_int();
    }

    int Tryte::to_int() const
    {
        return trits.at(0).val * 243 + trits.at(1).val * 81 + trits.at(2).val * 27 + trits.at(3).val * 9 + trits.at(4).val * 3 + trits.at(5).val;
    }

    std::string Tryte::to_str() const
    {
        return std::string() + hi_trybble().to_chr() + lo_trybble().to_chr();
    }

    const Tryte Tryte::MINUS_ONE("0Z");
    const Tryte Tryte::ZERO;
    const Tryte Tryte::ONE("01");
} // namespace termite