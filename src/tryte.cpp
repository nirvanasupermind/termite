#include <iostream>
#include <string>
#include <array>
#include <cmath>

#include "trit.h"
#include "trybble.h"
#include "tryte.h"

namespace termite
{
    Tryte::Tryte(const std::array<Trit, 6> &trits)
        : trits(trits)
    {
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

    int Tryte::to_int() const
    {
        return trits.at(0).val * 243 + trits.at(1).val * 81 + trits.at(2).val * 27 + trits.at(3).val * 9 + trits.at(4).val * 3 + trits.at(5).val;
    }

    Trybble Tryte::hi_trybble() const
    {
        return Trybble(std::array<Trit, 3>{trits.at(0), trits.at(1), trits.at(2)});
    }

    Trybble Tryte::lo_trybble() const
    {
        return Trybble(std::array<Trit, 3>{trits.at(3), trits.at(4), trits.at(5)});
    }

    std::string Tryte::to_tern() const
    {
        std::string result;

        for (int i = 0; i < 6; i++)
        {
            result.push_back(trits.at(i).to_chr());
        }

        return result;
    }

    std::string Tryte::to_hept() const
    {
        return {hi_trybble().to_chr(), lo_trybble().to_chr()};
    }

    const Tryte Tryte::ZERO;
} // namespace termite