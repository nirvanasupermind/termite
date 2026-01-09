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
    const TerFloat TerFloat::HALF = TerFloat::from_double(0.5);
    const TerFloat TerFloat::THREE_HALVES = TerFloat::from_double(1.5);

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

    TerFloat TerFloat::operator*(const TerFloat& other) const {
        Word result_sig = significand.mul32(other.significand).second;
        return TerFloat(result_sig, exponent + other.exponent + Word::TWO);
    }



    TerFloat TerFloat::operator-(const TerFloat& other) const {
        return operator+(-other);
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
        for (int i = 0; i < 8; i++) {
            result = result * (TerFloat::from_double(2.0) - operator*(result));
        }

        // result = result + result * (TerFloat::from_double(1.0) - operator*(result));
        // result = result + result * (TerFloat::from_double(1.0) - operator*(result));

        // for(int i = 0; i < 5; i++) {
        //     result = result*(TerFloat::THREE_HALVES - operator*(TerFloat::HALF) * result * result);
        // }
        return result;
    }

    TerFloat TerFloat::operator/(const TerFloat& other) const {
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
        return (TerFloat::from_double(1.5707963267948966) - *this).sin();
    }


    TerFloat TerFloat::tan() const {
        return sin() / cos();
    }

    // TerFloat TerFloat::sqrt() const {
    //     // std::cout << exponent.to_int32() << '\n';
    //     TerFloat result((Word::MIN_FLOAT_SIG + Word::MAX_FLOAT_SIG) / Word::TWO, exponent / Word::TWO);
    //     for(int i = 0; i < 10; i++) {
    //         result = (TerFloat::HALF) * (result + operator/(result));
    //     }
    //     return result;
    // }

    TerFloat TerFloat::operator-() const {
        return TerFloat(-significand, exponent);
    }

    std::string TerFloat::to_str() const {
        return std::to_string(((double)significand.to_int32()) / 4782969.0) + "*3^" + std::to_string(exponent.to_int32());
    }

}