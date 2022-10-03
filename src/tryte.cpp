// -*- tryte.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>

#include "typedefs.hpp"
#include "trybble.hpp"
#include "tryte.hpp"

namespace termite {
    const Tryte Tryte::ZERO(Trybble::ZERO, Trybble::ZERO);

    const Tryte Tryte::ONE(Trybble::ZERO, Trybble::ONE);

    Tryte::Tryte(const Trybble& hi, const Trybble& lo)
        : hi(hi), lo(lo) {
    }

    Tryte Tryte::from_i16(i16 num) {
        if (num < 0) {
            return Tryte::from_u16(num + 729);
        }

        return Tryte::from_u16(num);
    }

    Tryte Tryte::from_u16(u16 num) {
        u8 hi_num = num / 27;
        u8 lo_num = num % 27;

        return Tryte(Trybble::from_u8(hi_num), Trybble::from_u8(lo_num));
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
    
    i16 Tryte::to_i16() const {
        i16 result = to_u16();

        if (result > 364) {
            return result - 729;
        }

        return result;
    }

    u16 Tryte::to_u16() const {
        return hi.to_u8() * 27 + lo.to_u8();
    }

    std::string Tryte::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }

    std::string Tryte::to_sept_str() const {
        return std::string() + hi.to_sept_char() + lo.to_sept_char();
    }
} // namespace termite
