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
       return TerFloat(significand.shr_int8(7) *other.significand.shr_int8(7), exponent + other.exponent);
    }
    
        
    TerFloat TerFloat::operator/(const TerFloat& other) const {
       return TerFloat(significand / other.significand, exponent - other.exponent);
    }
    
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
            while(significand > Word::MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        } else if(significand < Word::ZERO) {
            while(significand > Word::NEG_MIN_FLOAT_SIG) {
                significand = significand.shl_int8(1);
                exponent = exponent - Word::ONE;
            }
            while(significand < Word::NEG_MAX_FLOAT_SIG) {
                significand = significand.shr_int8(1);
                exponent = exponent + Word::ONE;
            }
        }
    }

    TerFloat TerFloat::operator-() const {
        return TerFloat(-significand, exponent);
    }

    std::string TerFloat::to_str() const {
        return std::to_string(((double)significand.to_int32())/4782969.0) + "*3^" + std::to_string(exponent.to_int32());
    }

}