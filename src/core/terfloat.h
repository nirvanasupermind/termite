#ifndef TERFLOAT_H
#define TERFLOAT_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"
#include "word.h"

namespace termite {
    class TerFloat {
    protected:
        Word significand;
        Word exponent;
    public:
        static const Word ZERO;
        static const Word ONE;
        static const Word TWO;
        TerFloat();
        TerFloat(Word significand, Word exponent); // Not const& because I copy and modify them
        static TerFloat from_double(double n);
        void normalize();
        TerFloat operator-() const;
        TerFloat operator+(const TerFloat& other) const;
        TerFloat operator-(const TerFloat& other) const;
        TerFloat operator*(const TerFloat& other) const;
        TerFloat operator/(const TerFloat& other) const;
        std::string to_str() const;
    };
} // namespace termite

#endif