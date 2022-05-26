#ifndef TRYTE_H
#define TRYTE_H

#include <string>
#include <vector>

#include "trit.h"

namespace termite
{
    // A tryte is an integer containing 6 trits, using 3's complement-notation for negative integers.

    class Tryte
    {
    public:
        Tryte() = default;

        Tryte(int n);

        Tryte(const std::string &str);

        Tryte(Trit val[6]);

        // Negation
        Tryte operator-() const;

        // Addition
        Tryte operator+(const Tryte &b) const;

        // Subtraction
        Tryte operator-(const Tryte &b) const;
        
        // Multiplication
        Tryte operator*(const Tryte &b) const;
        
        // "Trit-wise" logical NOT
        Tryte operator~() const;

        // "Trit-wise" logical AND
        Tryte operator&(const Tryte &b) const;

        // "Trit-wise" logical OR
        Tryte operator|(const Tryte &b) const;

        // "Trit-wise" logical XOR
        Tryte operator^(const Tryte &b) const;

        // Equality
        bool operator==(const Tryte &b) const;

        // Inequality
        bool operator!=(const Tryte &b) const;

        // Integer representation
        int intVal() const;

        // String representation for debugging purposes
        std::string str() const;

        // Constant for the tryte with the value of 0
        static const Tryte ZERO;

        // Constant for the tryte with the value of 1
        static const Tryte ONE;

        static const int pow3[6];
    protected:
        // The 6 trits
        Trit val[6];

        // Ternary analogue to full adder
        Trit fulladder(Trit t1, Trit t2, Trit &carry) const;
    };
}

#endif