// -*- tryte.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>

#include "util.hpp"
#include "trybble.hpp"
#include "tryte.hpp"

namespace termite {
    const Tryte Tryte::ZERO(Trybble::ZERO, Trybble::ZERO);

    const Tryte Tryte::ONE(Trybble::ZERO, Trybble::ONE);

    const Tryte Tryte::TWO(Trybble::ZERO, Trybble::TWO);

    Tryte::Tryte(const Trybble& hi, const Trybble& lo)
        : hi(hi), lo(lo) {
    }

    Tryte::Tryte(NativeInt, int num) 
        : hi(Trybble(native_int, num / 27)), lo(Trybble(native_int, num % 27)) {
    }

    Tryte::Tryte(Sept, const std::string& str)
        : hi(Trybble(sept, std::string() + str[0])), lo(Trybble(sept, std::string() + str[1])) {
    }

    Tryte Tryte::operator&(const Tryte& other) const {
        return Tryte(hi & other.hi, lo & other.lo);
    }

    Tryte Tryte::operator|(const Tryte& other) const {
        return Tryte(hi | other.hi, lo | other.lo);
    }

    Tryte Tryte::operator^(const Tryte& other) const {
        return Tryte(hi ^ other.hi, lo ^ other.lo);
    }

    Tryte Tryte::operator~() const {
        return Tryte(~hi, ~lo);
    }

    Trybble Tryte::get_hi() const {
        return hi;
    }

    Trybble Tryte::get_lo() const {
        return lo;
    }

    Tryte::operator int() const {
        return hi * 27 + lo;
    }
    
    Tryte::operator std::string() const {
        return static_cast<std::string>(hi) + static_cast<std::string>(lo);
    }
} // namespace termite