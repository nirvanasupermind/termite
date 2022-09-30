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
        u8 quot = num / 27;
        u8 rem = num % 27;

        return Tryte(Trybble::from_u8(quot), Trybble::from_u8(rem));
    }

    Tryte Tryte::operator+(const Tryte& other) const {
        return Tryte::from_u16(to_u16() + other.to_u16());
    }

    Tryte Tryte::operator-(const Tryte& other) const {
        return Tryte::from_u16(to_u16() - other.to_u16());
    }

    Tryte Tryte::operator*(const Tryte& other) const {
        return Tryte::from_u16(to_u16() * other.to_u16());
    }

    Tryte Tryte::smul(const Tryte& other) const {
        return Tryte::from_i16(to_i16() * other.to_i16());
    }

    Tryte Tryte::operator/(const Tryte& other) const {
        return Tryte::from_u16(to_u16() / other.to_u16());
    }

    Tryte Tryte::sdiv(const Tryte& other) const {
        return Tryte::from_i16(to_i16() / other.to_i16());
    }

    Tryte Tryte::operator%(const Tryte& other) const {
        return Tryte::from_u16(to_u16() % other.to_u16());
    }

    Tryte Tryte::smod(const Tryte& other) const {
        return Tryte::from_i16(to_i16() % other.to_i16());
    }

    Tryte Tryte::operator-() const {
        return operator~() + Tryte::ONE;
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
