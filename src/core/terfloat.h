#ifndef TERFLOAT_H
#define TERFLOAT_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"
#include "word.h"

namespace termite {
    // Produces q ≈ (a / b) in QK (scaled by 3^K) without overflowing Word width.
    // Assumes a,b are Word (balanced ternary), b != 0.
    Word div_fixed_QK(Word a, Word b, int K);
    class TerFloat {
    // protected:
    public:
        Word significand;
        Word exponent;
    // public:
        static const TerFloat HALF;
        static const TerFloat THREE_HALVES;

        TerFloat();
        TerFloat(Word significand, Word exponent); // Not const& because I copy and modify them
        static TerFloat from_double(double n);
        void normalize();
        TerFloat operator-() const;
        TerFloat operator+(const TerFloat& other) const;
        TerFloat operator-(const TerFloat& other) const;
        TerFloat operator*(const TerFloat& other) const;
        TerFloat operator/(const TerFloat& other) const;
        TerFloat sqrt() const;

        std::string to_str() const;
    };
} // namespace termite

#endif