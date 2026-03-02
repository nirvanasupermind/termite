#include <cstdint>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "tryte.h"
#include "word.h"
#include "tables.h"
#include "terfloat.h"

namespace termite {
    const TerFloat TerFloat::ZERO = TerFloat::from_double(0.0);
    const TerFloat TerFloat::HALF = TerFloat::from_double(0.5);
    const TerFloat TerFloat::ONE = TerFloat::from_double(1.0);
    const TerFloat TerFloat::THREE_HALVES = TerFloat::from_double(1.5);
    const TerFloat TerFloat::NEGATIVE_INFINITY = TerFloat(Word::NEG_MIN_FLOAT_SIG, Word::from_int32(21523360));
    const TerFloat TerFloat::POSITIVE_INFINITY = TerFloat(Word::MIN_FLOAT_SIG, Word::from_int32(21523360));
    const TerFloat TerFloat::NAN_ = TerFloat(Word::MAX_FLOAT_SIG, Word::from_int32(21523360));
    TerFloat::TerFloat()
        : significand(Word::ZERO), exponent(Word::ZERO) {
    }

    TerFloat::TerFloat(Word significand, Word exponent)
        : significand(significand), exponent(exponent) {
        normalize();
    }

    TerFloat TerFloat::from_double(double n) {
        if (n < 0.0) {
            return -TerFloat::from_double(-n);
        }
        if (n == 0.0) return TerFloat(Word::ZERO, Word::ZERO);

        double log3n = std::log(n) / std::log(3);
        double exponent = std::floor(log3n);
        double significand = std::pow(3, (log3n - exponent) + 14);
        return TerFloat(Word::from_int32((int32_t)(std::round(significand))), Word::from_int32((int32_t)(exponent)));
    }

    TerFloat TerFloat::operator+(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }
        else if (operator==(TerFloat::POSITIVE_INFINITY)) {
            if (other == TerFloat::NEGATIVE_INFINITY) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::POSITIVE_INFINITY;
            }
        }
        else if (operator==(TerFloat::NEGATIVE_INFINITY)) {
            if (other == TerFloat::POSITIVE_INFINITY) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::NEGATIVE_INFINITY;
            }
        }
        TerFloat x = *this;
        TerFloat y = other;
        if (exponent < other.exponent) {
            std::swap(x, y);
        }
        Word sum = x.significand + y.significand.shr_int8(x.exponent.to_int32() - y.exponent.to_int32());
        Word shr1_sum = x.significand.shr_int8(1) + y.significand.shr_int8(1 + (x.exponent.to_int32() - y.exponent.to_int32()));
        if (shr1_sum > Word::MIN_FLOAT_SIG || shr1_sum < Word::NEG_MIN_FLOAT_SIG) {
            return TerFloat(shr1_sum, x.exponent + Word::ONE);
        }
        else {
            return TerFloat(x.significand + y.significand.shr_int8(x.exponent.to_int32() - y.exponent.to_int32()), x.exponent);
        }
    }




    TerFloat TerFloat::operator-(const TerFloat& other) const {
        return operator+(-other);
    }


    TerFloat TerFloat::operator*(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }
        else if (operator==(TerFloat::POSITIVE_INFINITY)) {
            if (other.significand < Word::ZERO) {
                return TerFloat::NEGATIVE_INFINITY;
            }
            else {
                return TerFloat::POSITIVE_INFINITY;
            }
        }
        else if (operator==(TerFloat::NEGATIVE_INFINITY)) {
            if (other.significand < Word::ZERO) {
                return TerFloat::POSITIVE_INFINITY;
            }
            else {
                return TerFloat::NEGATIVE_INFINITY;
            }
        }
        Word result_sig = significand.mul32(other.significand).second;
        return TerFloat(result_sig, exponent + other.exponent + Word::TWO);
    }


    void TerFloat::normalize() {
        if (significand == Word::ZERO) {
            exponent = Word::ZERO;
        }
        else if (significand > Word::ZERO) {
            while (significand < Word::MIN_FLOAT_SIG) {
                significand = significand.shl_int8(1);
                exponent = exponent - Word::ONE;
            }
            while (significand >= Word::MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        }
        else if (significand < Word::ZERO) {
            while (significand > Word::NEG_MIN_FLOAT_SIG) {
                significand = significand.shl_int8(1);
                exponent = exponent - Word::ONE;
            }
            while (significand <= Word::NEG_MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        }
    }


    TerFloat TerFloat::rec() const {
        TerFloat result(-(significand - Word::MIN_FLOAT_SIG) + Word::MAX_FLOAT_SIG, Word::from_int32(-1) - exponent);
        // std::cout << "dbg " << Word::MAX_FLOAT_SIG.to_int32() << '\n';
        // std::cout << "dbg " << (Word::MAX_FLOAT_SIG / (significand.shr_int8(2))).to_int32() << '\n';
        // TerFloat result((Word::MAX_FLOAT_SIG / (significand.shr_int8(7))).shl_int8(7), Word::from_int32(-1) - exponent);
        for (int i = 0; i < 8; i++) {
            result = result * (TerFloat::from_double(2.0) - operator*(result));
        }

        // result = result + result * (TerFloat::from_double(1.0) - operator*(result));
        // result = result + result * (TerFloat::from_double(1.0) - operator*(result));

        // for (int i = 0; i < 5; i++) {
        //     result = result * (TerFloat::THREE_HALVES - operator*(TerFloat::HALF) *result * result);
        // }
        return result;
    }

    TerFloat TerFloat::operator/(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }
        else if (is_inf()) {
            if (other.is_inf()) {
                return TerFloat::NAN_;
            }
            else {
                return TerFloat::ZERO;
            }
        }
        else if (operator==(TerFloat::ZERO)) {
            if (other.significand < Word::ZERO) {
                return TerFloat::NEGATIVE_INFINITY;
            }
            else {
                return TerFloat::POSITIVE_INFINITY;
            }
        }
        return operator*(other.rec());
    }


    TerFloat TerFloat::operator%(const TerFloat& other) const {
        return TerFloat::from_double(std::fmod(to_double(), other.to_double()));
        // return operator-(operator/(other).floor()*other);
    }

    TerFloat TerFloat::sqrt() const {
        if (significand < Word::ZERO) {
            return TerFloat(Word::ZERO, Word::ZERO); // or throw
        }

        TerFloat x(Word::MIN_FLOAT_SIG, exponent / Word::TWO); // ~1 * 3^(e/2)

        for (int i = 0; i < 8; i++) {
            x = (x + (*this / x)) / TerFloat::from_double(2.0);
        }
        return x;

    }

    double TerFloat::to_double() const {
        return significand.to_int32() * std::pow(3.0, exponent.to_int32() - 14.0);
    }

    TerFloat TerFloat::floor() const {
        return TerFloat::from_double(std::floor(to_double()));
    }

    TerFloat TerFloat::sin() const {
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        // Taylor serise iteration
        TerFloat x = operator%(TerFloat::from_double(6.283185307179586)); // reduce to 2π
        TerFloat x2 = x * x;

        TerFloat t1 = x;
        TerFloat t2 = x * x2 * TerFloat::from_double(1.0 / 6.0);      // x^3/6
        TerFloat t3 = x * x2 * x2 * TerFloat::from_double(1.0 / 120.0); // x^5/120
        TerFloat t4 = x * x2 * x2 * x2 * TerFloat::from_double(1.0 / 5040.0); // x^7/5040
        return t1 - t2 + t3 - t4;
    }

    TerFloat TerFloat::cos() const {
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        return (TerFloat::from_double(1.5707963267948966) - *this).sin();
    }


    TerFloat TerFloat::tan() const {
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        return sin() / cos();
    }

    TerFloat TerFloat::atan() const {
        if (is_inf_or_nan()) {
            return TerFloat::NAN_;
        }
        if (significand < Word::ZERO) {
            return -operator-().atan();
        }
        else if (to_double() > 1.0) {
            return TerFloat::from_double(1.5707963267948966) - rec().atan();
        }
        else {
            TerFloat x = *this;
            TerFloat x2 = x * x;


            // Coefficients computed by me using numpy polynomial regression because taylor series is too slow

            TerFloat t1 = x * TerFloat::from_double(1.00005597e+00);
            TerFloat t2 = x2 * TerFloat::from_double(-1.28153654e-03);
            TerFloat t3 = x * x2 * TerFloat::from_double(-3.20855563e-01);
            TerFloat t4 = x2 * x2 * TerFloat::from_double(-6.33708278e-02);
            TerFloat t5 = x * x2 * x2 * TerFloat::from_double(3.82629843e-01);
            TerFloat t6 = x * x2 * x2 * x2 * TerFloat::from_double(-2.99476356e-01);
            TerFloat t7 = x * x2 * x2 * x2 * x2 * TerFloat::from_double(9.92837258e-02);
            TerFloat t8 = x2 * x2 * x2 * x2 * x2 * TerFloat::from_double(-1.15861248e-02);

            //                 TerFloat t0 = TerFloat::from_double(-1.15861248e-02);
    // TerFloat t1 = x * TerFloat::from_double(  9.92837258e-02);
    // TerFloat t2 = x2 * TerFloat::from_double(-4.42298621e+00);
    // TerFloat t3 = x * x2 * TerFloat::from_double(-2.99476356e-01);
    // TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
    // TerFloat t5 = x * x2 * x2 * TerFloat::from_double(3.82629843e-01);
    // TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-6.33708278e-02);
    // TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(-3.20855563e-01);
    // TerFloat t8 = x2 * x2 * x2 * x2 * TerFloat::from_double(-1.28153654e-03);
            return t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8;
        }
    }


    TerFloat TerFloat::exp() const {
        if (operator==(TerFloat::NEGATIVE_INFINITY)) {
            return TerFloat::ZERO;
        }
        else if (operator==(TerFloat::POSITIVE_INFINITY)) {
            return TerFloat::POSITIVE_INFINITY;
        }
        else if (is_nan()) {
            return TerFloat::NAN_;
        }

        if (to_double() < 0.0) {
            return operator-().exp().rec();
        }
        if (to_double() >= 1.0) {
            TerFloat temp = operator/(TerFloat::from_double(2.0)).exp();
            return temp * temp;
        }
        // Taylor serises iteration
        TerFloat x = *this;
        TerFloat x2 = x * x;

        TerFloat t0 = TerFloat::from_double(1.0);
        TerFloat t1 = x;
        TerFloat t2 = x2 * TerFloat::from_double(1.0 / 2.0); // x^2/2
        TerFloat t3 = x * x2 * TerFloat::from_double(1.0 / 6.0); // x^3/6
        TerFloat t4 = x2 * x2 * TerFloat::from_double(1.0 / 24.0); // x^4/24
        TerFloat t5 = x * x2 * x2 * TerFloat::from_double(1.0 / 120.0); // x^5/120
        TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(1.0 / 720.0); // x^6/720
        TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(1.0 / 5040.0); // x^7/5040


        return t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7;
    }



    TerFloat TerFloat::log() const {
        if (operator==(TerFloat::ZERO)) {
            return TerFloat::NEGATIVE_INFINITY;
        }
        else if (significand < Word::ZERO || is_inf_or_nan()) {
            return TerFloat::NAN_;
        }

        if (to_double() >= 3.0) {
            return TerFloat(significand, exponent - Word::ONE).log() + TerFloat::from_double(std::log(3));
        }
        TerFloat x(significand, Word::ZERO);
        TerFloat x2 = x * x;
        // Coefficients computed by me using numpy polynomial regression because taylor series is too slow
        TerFloat t0 = TerFloat::from_double(-2.15992321e+00);
        TerFloat t1 = x * TerFloat::from_double(4.53754024e+00);
        TerFloat t2 = x2 * TerFloat::from_double(-4.42298621e+00);
        TerFloat t3 = x * x2 * TerFloat::from_double(3.22668318e+00);
        TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
        TerFloat t5 = x * x2 * x2 * TerFloat::from_double(5.50260978e-01);
        TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-1.19227045e-01);
        TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(1.49458088e-02);
        TerFloat t8 = x2 * x2 * x2 * x2 * TerFloat::from_double(-8.24182119e-04);
        // TerFloat t0 = TerFloat::from_double(-8.24182119e-04);
        // TerFloat t1 = x * TerFloat::from_double(1.49458088e-02);
        // TerFloat t2 = x2 * TerFloat::from_double(-1.19227045e-01);
        // TerFloat t3 = x * x2 * TerFloat::from_double(5.50260978e-01);
        // TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
        // TerFloat t5 = x * x2 * x2 * TerFloat::from_double(3.22668318e+00); // x^6/720
        // TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-4.42298621e+00);
        // TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(4.53754024e+00);
        // TerFloat t8 = x2 * x2 * x2 * x2 * TerFloat::from_double(-2.15992321e+00);
        return t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8;
    }

    TerFloat TerFloat::abs() const {
        if (significand < Word::ZERO) {
            return operator-();
        }
        else {
            return *this;
        }
    }

    TerFloat TerFloat::operator-() const {
        return TerFloat(-significand, exponent);
    }

    bool TerFloat::is_nan() const {
        return exponent.to_int32() == 21523360 && significand != Word::NEG_MIN_FLOAT_SIG && significand != Word::MIN_FLOAT_SIG;
    }

    bool TerFloat::is_inf() const {
        return exponent.to_int32() == 21523360 && (significand == Word::NEG_MIN_FLOAT_SIG || significand == Word::MIN_FLOAT_SIG);
    }

    bool TerFloat::is_finite() const {
        return exponent.to_int32() != 21523360;
    }


    bool TerFloat::is_inf_or_nan() const {
        return exponent.to_int32() == 21523360;
    }

    bool TerFloat::operator==(const TerFloat& other) const {
        return exponent == other.exponent && significand == other.significand;
    }

    bool TerFloat::operator!=(const TerFloat& other) const {
        return !operator==(other);
    }

    bool TerFloat::operator<(const TerFloat& other) const {
        return operator-(other).significand < Word::ZERO;
    }


    bool TerFloat::operator<=(const TerFloat& other) const {
        return operator-(other).significand <= Word::ZERO;
    }

    bool TerFloat::operator>(const TerFloat& other) const {
        return operator-(other).significand > Word::ZERO;
    }


    bool TerFloat::operator>=(const TerFloat& other) const {
        return operator-(other).significand >= Word::ZERO;
    }

    std::string TerFloat::to_str() const {
        if (operator==(TerFloat::POSITIVE_INFINITY)) {
            return "inf";
        }
        else if (operator==(TerFloat::NEGATIVE_INFINITY)) {
            return "-inf";
        }
        else if (is_nan()) {
            return "nan";
        }
        if (significand == Word::ZERO) {
            return "0.000000";
        }
        if (!std::isinf(to_double()) && to_double() != 0) {
            return std::to_string(to_double());
        }
        else {
            double log10_val = ((double)(exponent.to_int32()) * std::log10(3)) + std::log10((double)(significand.to_int32()) / 4782969.0);
            double decimal_exp = std::floor(log10_val);
            double decimal_sig = std::pow(10.0, log10_val - decimal_exp);
            if (decimal_exp > 0) {
                return std::to_string(decimal_sig) + "e+" + std::to_string((int)decimal_exp);
            }
            else {
                return std::to_string(decimal_sig) + "e-" + std::to_string((int)(-decimal_exp));
            }
        }

        // return std::to_string(((double)significand.to_int32()) / 4782969.0) + "*3^" + std::to_string(exponent.to_int32());
    }

}