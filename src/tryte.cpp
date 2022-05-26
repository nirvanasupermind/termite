#include <iostream>
#include <string>

#include "trit.h"
#include "tryte.h"

namespace termite
{
    Tryte::Tryte(int n)
    {
        int i = 0;
        while (n > 0)
        {
            int rem = n % 3;
            n = n / 3;
            if (rem == 2)
            {
                rem = -1;
                n++;
            }
            val[i] = rem;
            i++;
        }
    }

    Tryte::Tryte(const std::string &str)
    {
        for (int i = 5; i >= 0; i--)
        {
            val[i] = Trit::fromChar(str.at(i));
        }
    }

    Tryte::Tryte(Trit val[6])
    {
        std::copy(val, val + 6, this->val);
    }

    Tryte Tryte::operator-() const
    {
        return operator~();
    }

    Tryte Tryte::operator+(const Tryte &b) const
    {
        Trit carry = 0;

        Trit result[6];

        for (int i = 5; i >= 0; i--)
        {
            result[i] = fulladder(val[i], b.val[i], carry);
        }

        return result;
    }

    Tryte Tryte::operator-(const Tryte &b) const
    {
        return operator+(-b);
    }

    Tryte Tryte::operator*(const Tryte &b) const
    {
        Tryte pos = *this;

        Tryte neg = operator-();

        Tryte result;

        for (int i = 5; i >= 0; i--)
        {
            Trit trit = b.val[i];

            Tryte posOrNeg = (trit == 0 ? Tryte::ZERO : (trit == 1 ? pos : neg));

            Tryte adder;

            std::copy(posOrNeg.val, posOrNeg.val + 6, adder.val);

            for (int j = 0; j < i; j++)
            {
                adder.val[j] = adder.val[j + (5 - i)];
            }

            for (int k = i; k < 5; k++)
            {
                adder.val[k] = 0;
            }

            result = result + adder;
        }

        return result;
    }

    Tryte Tryte::operator~() const
    {
        Trit result[6];

        for (int i = 0; i < 6; i++)
        {
            result[i] = !val[i];
        }

        return result;
    }

    Tryte Tryte::operator&(const Tryte &b) const
    {
        Trit result[6];

        for (int i = 0; i < 6; i++)
        {
            result[i] = val[i] && b.val[i];
        }

        return result;
    }

    Tryte Tryte::operator|(const Tryte &b) const
    {
        Trit result[6];

        for (int i = 0; i < 6; i++)
        {
            result[i] = val[i] || b.val[i];
        }

        return result;
    }

    Tryte Tryte::operator^(const Tryte &b) const
    {
        Trit result[6];

        for (int i = 0; i < 6; i++)
        {
            result[i] = val[i] ^ b.val[i];
        }

        return result;
    }

    int Tryte::intVal() const
    {
        int result = 0;

        for (int i = 5; i >= 0; i--)
        {
            result += val[i].val * Tryte::pow3[i];
        }

        return result;
    }


    std::string Tryte::str() const
    {
        std::string result;
        for (int i = 0; i < 6; i++)
        {
            result.push_back(val[i].charVal());
        }
        return result;
    }

    Trit Tryte::fulladder(Trit t1, Trit t2, Trit &carry) const
    {
        unsigned char s = (unsigned char)t1.val + (unsigned char)t2.val + (unsigned char)carry.val;
        carry = s / 3;
        return s % 3;
    }

    const Tryte Tryte::ZERO;
    const Tryte Tryte::ONE("000001");

    const int Tryte::pow3[6] = { 243, 81, 27, 9, 3, 1 }; 
}