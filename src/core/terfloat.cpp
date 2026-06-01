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
    // sqrt(1), sqrt(82/81), sqrt(83/81),..., sqrt(241/81), sqrt(242/81) (ends right before sqrt(3))
    const Word TerFloat::SQRT_LOOKUP_TABLE[162] = {Word::from_int32(4782969),Word::from_int32(4812403),Word::from_int32(4841658),Word::from_int32(4870737),Word::from_int32(4899644),Word::from_int32(4928381),Word::from_int32(4956952),Word::from_int32(4985358),Word::from_int32(5013604),Word::from_int32(5041692),Word::from_int32(5069624),Word::from_int32(5097403),Word::from_int32(5125031),Word::from_int32(5152512),Word::from_int32(5179846),Word::from_int32(5207037),Word::from_int32(5234087),Word::from_int32(5260997),Word::from_int32(5287771),Word::from_int32(5314410),Word::from_int32(5340916),Word::from_int32(5367291),Word::from_int32(5393537),Word::from_int32(5419656),Word::from_int32(5445650),Word::from_int32(5471520),Word::from_int32(5497268),Word::from_int32(5522897),Word::from_int32(5548407),Word::from_int32(5573800),Word::from_int32(5599078),Word::from_int32(5624243),Word::from_int32(5649295),Word::from_int32(5674237),Word::from_int32(5699070),Word::from_int32(5723795),Word::from_int32(5748413),Word::from_int32(5772927),Word::from_int32(5797337),Word::from_int32(5821644),Word::from_int32(5845851),Word::from_int32(5869958),Word::from_int32(5893966),Word::from_int32(5917877),Word::from_int32(5941691),Word::from_int32(5965410),Word::from_int32(5989036),Word::from_int32(6012569),Word::from_int32(6036009),Word::from_int32(6059360),Word::from_int32(6082620),Word::from_int32(6105792),Word::from_int32(6128877),Word::from_int32(6151874),Word::from_int32(6174786),Word::from_int32(6197614),Word::from_int32(6220357),Word::from_int32(6243018),Word::from_int32(6265597),Word::from_int32(6288095),Word::from_int32(6310512),Word::from_int32(6332850),Word::from_int32(6355110),Word::from_int32(6377292),Word::from_int32(6399397),Word::from_int32(6421426),Word::from_int32(6443380),Word::from_int32(6465259),Word::from_int32(6487064),Word::from_int32(6508796),Word::from_int32(6530456),Word::from_int32(6552045),Word::from_int32(6573562),Word::from_int32(6595009),Word::from_int32(6616387),Word::from_int32(6637696),Word::from_int32(6658937),Word::from_int32(6680110),Word::from_int32(6701216),Word::from_int32(6722256),Word::from_int32(6743230),Word::from_int32(6764140),Word::from_int32(6784984),Word::from_int32(6805765),Word::from_int32(6826483),Word::from_int32(6847138),Word::from_int32(6867731),Word::from_int32(6888263),Word::from_int32(6908733),Word::from_int32(6929143),Word::from_int32(6949493),Word::from_int32(6969783),Word::from_int32(6990015),Word::from_int32(7010188),Word::from_int32(7030304),Word::from_int32(7050362),Word::from_int32(7070363),Word::from_int32(7090307),Word::from_int32(7110196),Word::from_int32(7130029),Word::from_int32(7149807),Word::from_int32(7169531),Word::from_int32(7189201),Word::from_int32(7208816),Word::from_int32(7228379),Word::from_int32(7247889),Word::from_int32(7267346),Word::from_int32(7286752),Word::from_int32(7306106),Word::from_int32(7325409),Word::from_int32(7344661),Word::from_int32(7363863),Word::from_int32(7383014),Word::from_int32(7402117),Word::from_int32(7421170),Word::from_int32(7440174),Word::from_int32(7459130),Word::from_int32(7478038),Word::from_int32(7496898),Word::from_int32(7515711),Word::from_int32(7534477),Word::from_int32(7553196),Word::from_int32(7571869),Word::from_int32(7590496),Word::from_int32(7609077),Word::from_int32(7627613),Word::from_int32(7646105),Word::from_int32(7664551),Word::from_int32(7682953),Word::from_int32(7701312),Word::from_int32(7719626),Word::from_int32(7737898),Word::from_int32(7756126),Word::from_int32(7774312),Word::from_int32(7792455),Word::from_int32(7810556),Word::from_int32(7828615),Word::from_int32(7846632),Word::from_int32(7864609),Word::from_int32(7882544),Word::from_int32(7900438),Word::from_int32(7918293),Word::from_int32(7936107),Word::from_int32(7953881),Word::from_int32(7971615),Word::from_int32(7989310),Word::from_int32(8006966),Word::from_int32(8024583),Word::from_int32(8042162),Word::from_int32(8059702),Word::from_int32(8077204),Word::from_int32(8094668),Word::from_int32(8112095),Word::from_int32(8129484),Word::from_int32(8146836),Word::from_int32(8164152),Word::from_int32(8181430),Word::from_int32(8198672),Word::from_int32(8215878),Word::from_int32(8233049),Word::from_int32(8250183),Word::from_int32(8267282)};
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
    if (is_nan() || other.is_nan()) return TerFloat::NAN_;

    if (*this == TerFloat::ZERO || other == TerFloat::ZERO) {
        return TerFloat::ZERO;
    }

    if (is_inf() || other.is_inf()) {
        bool neg = (significand < Word::ZERO) ^ (other.significand < Word::ZERO);
        return neg ? TerFloat::NEGATIVE_INFINITY : TerFloat::POSITIVE_INFINITY;
    }

    std::pair<Word, Word> mul32_res = significand.mul32(other.significand);

    std::cout << "DBG99" << (significand.to_int32()) << '\n';
    std::cout << "DBG100 " << mul32_res.first.to_int32() << ' '  << mul32_res.second.to_int32() << '\n';
    Word result_significand = mul32_res.second.shl_int8(2) + mul32_res.first.shr_int8(14);
    return TerFloat(result_significand, exponent + other.exponent);
}

    // TerFloat TerFloat::operator*(const TerFloat& other) const {
    //     if (is_nan() || other.is_nan()) {
    //         return TerFloat::NAN_;
    //     }
    //     else if (operator==(TerFloat::POSITIVE_INFINITY)) {
    //         if (other.significand < Word::ZERO) {
    //             return TerFloat::NEGATIVE_INFINITY;
    //         }
    //         else {
    //             return TerFloat::POSITIVE_INFINITY;
    //         }
    //     }
    //     else if (operator==(TerFloat::NEGATIVE_INFINITY)) {
    //         if (other.significand < Word::ZERO) {
    //             return TerFloat::POSITIVE_INFINITY;
    //         }
    //         else {
    //             return TerFloat::NEGATIVE_INFINITY;
    //         }
    //     }
    //     Word result_sig = significand.mul32(other.significand).second;
    //     return TerFloat(result_sig, exponent + other.exponent + Word::TWO);
    // }


    void TerFloat::normalize() {
        if (significand == Word::ZERO) {
            exponent = Word::ZERO;
        }
        else if (significand > Word::ZERO) {
            if (significand < Word::MIN_FLOAT_SIG) {
                while (significand < Word::MIN_FLOAT_SIG) {
                    significand = significand.shl_int8(1);
                    exponent = exponent - Word::ONE;
                }
            }
            else if (significand <= Word::MAX_FLOAT_SIG) {
                while (significand >= Word::MAX_FLOAT_SIG) {
                    significand = significand.shr_int8(1);
                    exponent = exponent + Word::ONE;
                }
            }
        }
        else if (significand < Word::ZERO) {
            if (significand > Word::NEG_MIN_FLOAT_SIG) {
                while (significand > Word::NEG_MIN_FLOAT_SIG) {
                    significand = significand.shl_int8(1);
                    exponent = exponent - Word::ONE;
                }
            }
            else if (significand <= Word::NEG_MAX_FLOAT_SIG) {
                while (significand <= Word::NEG_MAX_FLOAT_SIG) {
                    significand = significand.shr_int8(1);
                    exponent = exponent + Word::ONE;
                }
            }
        }
    }


    TerFloat TerFloat::rec() const {
        if (exponent != Word::ZERO) {
            TerFloat unscaled_result = TerFloat(significand, Word::ZERO).rec();
            return TerFloat(unscaled_result.significand, -(exponent + Word::ONE));
        }

        // Trying to compute 1/x
        // Exponent = 0 so this is a number between 1 and 3
        // Using taylor series of 1/x centered at a=2
        // 1/x = 1/2 - 1/4(x-2) + 1/8(x-2)^2 - 1/16(x-2)^3 + 1/32(x-2)^4...

        TerFloat x_minus_a = operator-(TerFloat::from_double(2.0));
        TerFloat minus_half = TerFloat::from_double(-0.5);
        TerFloat minus_half_x_minus_a = x_minus_a * minus_half;
        TerFloat t0 = TerFloat::from_double(0.5);
        TerFloat t1 = t0 * minus_half_x_minus_a;
        TerFloat t2 = t1 * minus_half_x_minus_a;
        TerFloat t3 = t2 * minus_half_x_minus_a;
        TerFloat t4 = t3 * minus_half_x_minus_a;
        TerFloat t5 = t4 * minus_half_x_minus_a;
        TerFloat t6 = t5 * minus_half_x_minus_a;
        TerFloat t7 = t6 * minus_half_x_minus_a;
        // TerFloat t8 = t7 * minus_half_x_minus_a;


        TerFloat result = t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7;
        // for (int i = 0; i < 5; i++) {
        //     result = result * (TerFloat::THREE_HALVES - operator*(TerFloat::HALF) *result * result);
        // }
        return result;
    }
    // TerFloat TerFloat::operator/(const TerFloat& other) const {
    //     if (is_nan() || other.is_nan()) return TerFloat::NAN_;
    //     if (other == TerFloat::ZERO) {
    //         return significand < Word::ZERO ? TerFloat::NEGATIVE_INFINITY
    //                                         : TerFloat::POSITIVE_INFINITY;
    //     }
    //     if (*this == TerFloat::ZERO) return TerFloat::ZERO;

    //     if (is_inf() && other.is_inf()) return TerFloat::NAN_;
    //     if (is_inf()) {
    //         return (significand < Word::ZERO) ^ (other.significand < Word::ZERO)
    //             ? TerFloat::NEGATIVE_INFINITY
    //             : TerFloat::POSITIVE_INFINITY;
    //     }
    //     if (other.is_inf()) return TerFloat::ZERO;

    //     int64_t sa = significand.to_int32();
    //     int64_t sb = other.significand.to_int32();

    //     bool neg = (sa < 0) ^ (sb < 0);
    //     sa = std::llabs(sa);
    //     sb = std::llabs(sb);

    //     // scale into significand range
    //     static constexpr int64_t P14 = 4782969;   // 3^14
    //     static constexpr int64_t P15 = 14348907;  // 3^15

    //     int32_t out_exp = exponent.to_int32() - other.exponent.to_int32();

    //     // start with 3^14 scaling
    //     int64_t num = sa * P14;
    //     int64_t q = num / sb;
    //     int64_t r = num % sb;

    //     // round to nearest
    //     if (2 * r > sb || (2 * r == sb && (q % 2 != 0))) {
    //         q++;
    //     }

    //     // renormalize if needed
    //     while (q < P14) {
    //         q *= 3;
    //         out_exp -= 1;
    //     }
    //     while (q >= P15) {
    //         q /= 3;
    //         out_exp += 1;
    //     }

    //     if (neg) q = -q;

    //     return TerFloat(Word::from_int32((int32_t)q), Word::from_int32(out_exp));
    // }

    TerFloat TerFloat::operator/(const TerFloat& other) const {
        if (is_nan() || other.is_nan()) {
            return TerFloat::NAN_;
        }

        if (other == TerFloat::ZERO) {
            return TerFloat::POSITIVE_INFINITY;
        }
        if (*this == TerFloat::ZERO) {
            return TerFloat::ZERO;
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

        std::pair<Word, Word> exponent_divmod = exponent.divmod(Word::TWO);
        std::cout << "DBG" << significand.to_int32() << '\n';
        TerFloat x(SQRT_LOOKUP_TABLE[(significand.shr_int8(10)).to_int32() - 81], exponent_divmod.first); // ~1 * 3^(e/2)
        if(exponent_divmod.second != Word::ZERO) {
            x = x * TerFloat::from_double(std::sqrt(3.0));
        }
        for (int i = 0; i < 3; i++) {
            x = (x + (*this / x)) * TerFloat::from_double(0.5);
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
        // Taylor series iteration
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
            return TerFloat(significand, exponent - Word::ONE).log() + TerFloat::from_double(std::log(3.0));
        }
        TerFloat xMinusA = operator-(TerFloat::from_double(2.0));
        TerFloat t0 = TerFloat::from_double(0.6931471805599453);
        TerFloat t1 = TerFloat::from_double(0.5) * xMinusA; // 1/2(x-2)
        TerFloat t2 = TerFloat::from_double(-0.25) * xMinusA * t1; // -1/8(x-2)^2
        TerFloat t3 = TerFloat::from_double(-0.3333333333333333) * xMinusA * t2; // 1/24(x-2)^3
        TerFloat t4 = TerFloat::from_double(-0.375) * xMinusA * t3; // -1/64(x-2)^4
        TerFloat t5 = TerFloat::from_double(-0.4) * xMinusA * t4; // 1/160(x-2)^5
        TerFloat t6 = TerFloat::from_double(-0.41666666666666663) * xMinusA * t5; // 1/384(x-2)^6
        TerFloat t7 = TerFloat::from_double(0.42857142857142855) * xMinusA * t6; // 1/384(x-2)^7


        // Coefficients computed by me using numpy polynomial regression because taylor series is too slow
        // TerFloat t0 = TerFloat::from_double(-2.15992321e+00);
        // TerFloat t1 = x * TerFloat::from_double(4.53754024e+00);
        // TerFloat t2 = x2 * TerFloat::from_double(-4.42298621e+00);
        // TerFloat t3 = x * x2 * TerFloat::from_double(3.22668318e+00);
        // TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
        // TerFloat t5 = x * x2 * x2 * TerFloat::from_double(5.50260978e-01);
        // TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-1.19227045e-01);
        // TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(1.49458088e-02);
        // TerFloat t0 = TerFloat::from_double(-2.15992321e+00);
        // TerFloat t1 = x * TerFloat::from_double(4.53754024e+00);
        // TerFloat t2 = x2 * TerFloat::from_double(-4.42298621e+00);
        // TerFloat t3 = x * x2 * TerFloat::from_double(3.22668318e+00);
        // TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
        // TerFloat t5 = x * x2 * x2 * TerFloat::from_double(5.50260978e-01);
        // TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-1.19227045e-01);
        // TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(1.49458088e-02);
        // TerFloat t8 = x2 * x2 * x2 * x2 * TerFloat::from_double(-8.24182119e-04);
        // TerFloat t0 = TerFloat::from_double(-8.24182119e-04);
        // TerFloat t1 = x * TerFloat::from_double(1.49458088e-02);
        // TerFloat t2 = x2 * TerFloat::from_double(-1.19227045e-01);
        // TerFloat t3 = x * x2 * TerFloat::from_double(5.50260978e-01);
        // TerFloat t4 = x2 * x2 * TerFloat::from_double(-1.62646402e+00);
        // TerFloat t5 = x * x2 * x2 * TerFloat::from_double(3.22668318e+00); // x^6/720
        // TerFloat t6 = x2 * x2 * x2 * TerFloat::from_double(-4.42298621e+00);
        // TerFloat t7 = x * x2 * x2 * x2 * TerFloat::from_double(4.53754024e+00);
        // TerFloat t8 = x2 * x2 * x2 * x2 * TerFloat::from_double(-2.15992321e+00);
        return t0 + t1 + t2 + t3 + t4 + t5 + t6 + t7;
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
        if (!std::isinf(to_double()) && to_double() != 0 && to_double() < 1e+21 && to_double() > -1e+21) {
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