#ifndef TERFLOAT_H
#define TERFLOAT_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"
#include "word.h"

namespace termite {
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
        TerFloat rec() const;
        TerFloat operator/(const TerFloat& other) const;
        TerFloat operator%(const TerFloat& other) const;
        TerFloat sqrt() const;
        double to_double() const;
        TerFloat floor() const;
        TerFloat sin() const;
        TerFloat cos() const;
        TerFloat tan() const;
        TerFloat exp() const;
        TerFloat log() const;
        TerFloat abs() const;
        std::string to_str() const;
    };
} // namespace termite

#endif