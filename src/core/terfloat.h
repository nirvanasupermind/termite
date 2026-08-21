#ifndef TERFLOAT_H
#define TERFLOAT_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"
#include "word.h"

namespace termite {
    // class TerFloat {
    //     // protected:
    // public:
    //     Word significand;
    //     Word exponent;
    //     TerFloat();
    //     TerFloat(Word significand, Word exponent); // Not const& because I copy and modify them
    //     void normalize();
    // };
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
        static const TerFloat PI;
        static const TerFloat TWO_PI;
        static const TerFloat HALF_PI;
        static const TerFloat QUARTER_PI;
        static const TerFloat SQRT2_MINUS_1;
        static const TerFloat NEGATIVE_INFINITY;
        static const TerFloat POSITIVE_INFINITY;
        static const TerFloat NAN_;
        static const Word REC_LOOKUP_TABLE[162];
        static const Word RSQRT_LOOKUP_TABLE[162];

        // static const Word SQRT_LOOKUP_TABLE[162];


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
        TerFloat rsqrt() const;
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