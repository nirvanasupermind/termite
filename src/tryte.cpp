// -*- tryte.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>

#include "trybble.hpp"
#include "tryte.hpp"
#include "util.hpp"

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
        : hi(Trybble(sept, str.at(0))), lo(Trybble(sept, str.at(1))) {
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

    Tryte::operator unsigned int() const {
        return static_cast<unsigned int>(hi) * 27 + static_cast<unsigned int>(lo);
    }
    
    Tryte::operator std::string() const {
        return std::string() + static_cast<char>(hi) + static_cast<char>(lo);
    }
} // namespace termite