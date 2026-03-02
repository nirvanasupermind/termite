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
        static const TerFloat ZERO;
    static const TerFloat HALF;
        static const TerFloat ONE;

    static const TerFloat THREE_HALVES;
        static const TerFloat NEGATIVE_INFINITY;
        static const TerFloat POSITIVE_INFINITY;
        static const TerFloat NAN_;        
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
        TerFloat atan() const;
        TerFloat exp() const;
        TerFloat log() const;
        TerFloat abs() const;
        bool is_nan() const;
        bool is_inf() const;
        bool is_finite() const;
        bool is_inf_or_nan() const;
        bool operator==(const TerFloat& other) const;
        bool operator!=(const TerFloat& other) const;
        bool operator<(const TerFloat& other) const;
        bool operator<=(const TerFloat& other) const;
        bool operator>(const TerFloat& other) const;
        bool operator>=(const TerFloat& other) const;
        std::string to_str() const;
    };
} // namespace termite

#endif