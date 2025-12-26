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
    const TerFloat TerFloat::HALF(Word(1789569706), Word(1431655764));
    const TerFloat TerFloat::THREE_HALVES(Word(1789569706), Word(1431655765));

    TerFloat::TerFloat()
        : significand(Word::ZERO), exponent(Word::ZERO) {        
    }

    TerFloat::TerFloat(Word significand, Word exponent) 
    : significand(significand), exponent(exponent) {
        normalize();
    }

    TerFloat TerFloat::from_double(double n) {
        if(n < 0) {
            return -TerFloat::from_double(-n);
        }
        double log3n = std::log(n)/std::log(3);
        double exponent = std::floor(log3n);
        double significand = std::pow(3, (log3n - exponent) + 14);
        return TerFloat(Word::from_int32((int32_t)(std::round(significand))),Word::from_int32((int32_t)(exponent)));
    }

    TerFloat TerFloat::operator+(const TerFloat& other) const {
        TerFloat x = *this;
        TerFloat y = other;
        if(exponent < other.exponent) {
            std::swap(x, y);
        }
        Word shr1_sum = x.significand.shr_int8(1) + y.significand.shr_int8(1 + (x.exponent.to_int32() - y.exponent.to_int32()));
        if(shr1_sum > Word::MIN_FLOAT_SIG || shr1_sum < Word::NEG_MIN_FLOAT_SIG) {
            return TerFloat(shr1_sum, x.exponent);
        } else {
            return TerFloat(x.significand + y.significand.shr_int8(x.exponent.to_int32() - y.exponent.to_int32()), x.exponent);
        }
    }

    TerFloat TerFloat::operator*(const TerFloat& other) const {
    Word a = significand.shr_int8(7);
    Word b = other.significand.shr_int8(7);

    auto [lo, hi] = a.mul32_ref(b); // (lo + hi*3^16)

    // After shrinking both by 3^7, product is scaled by 3^14 overall,
    // which matches what we want (since original wants /3^14).
    // We now need a 16-trit significand. The "best" 16 trits depends on magnitude:
    // Usually you'd take the HIGH word for stability, but normalization expects
    // sig in [3^14, 3^15), so you typically want something around that.
    //
    // Simple first cut: take hi as significand and adjust exponent accordingly.
    // If you take hi, that effectively divides by 3^16 relative to lo+hi*3^16.
    // So you must compensate exponent by +16 trits => +16 in exponent (base-3 exponent units).
    //
    // But note: your exponent counts powers of 3^1, not 3^16.
    // Shifting by 16 trits equals multiplying/dividing by 3^16.
    //
    // If we choose hi, exp += 16.
    Word sig = hi;
    Word exp = exponent + other.exponent + Word::from_int32(16);

    return TerFloat(sig, exp);
}

    // TerFloat TerFloat::operator*(const TerFloat& other) const {
    //    return TerFloat(significand.shr_int8(7) *other.significand.shr_int8(7), exponent + other.exponent);
    // }
    
        
    

    TerFloat TerFloat::operator-(const TerFloat& other) const {
        return operator+(-other);
    }
    

    void TerFloat::normalize() {
        if(significand == Word::ZERO) {
            exponent = Word::ZERO;
        } else if(significand > Word::ZERO) {
            while(significand < Word::MIN_FLOAT_SIG) {
                significand = significand.shl_int8(1);
                exponent = exponent - Word::ONE;
            }
            while(significand >= Word::MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        } else if(significand < Word::ZERO) {
            while(significand > Word::NEG_MIN_FLOAT_SIG) {
                significand = significand.shl_int8(1);
                exponent = exponent - Word::ONE;
            }
            while(significand <= Word::NEG_MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        }
    }


    TerFloat TerFloat::rec() const {
        TerFloat result(-(significand - Word::MIN_FLOAT_SIG) + Word::MAX_FLOAT_SIG, Word::from_int32(-1) - exponent);
        for(int i = 0; i < 4; i++) {
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

    TerFloat TerFloat::sqrt() const {
        TerFloat result(significand, exponent / Word::TWO);
        for(int i = 0; i < 5; i++) {
            result = result*(TerFloat::THREE_HALVES - operator*(TerFloat::HALF) * result * result);
        }
        return result;
    }

    TerFloat TerFloat::operator-() const {
        return TerFloat(-significand, exponent);
    }

    std::string TerFloat::to_str() const {
        return std::to_string(((double)significand.to_int32())/4782969.0) + "*3^" + std::to_string(exponent.to_int32());
    }

}