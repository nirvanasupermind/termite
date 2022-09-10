#include <cstdint>
#include <string>
#include <exception>
#include <algorithm>

#include "util.hpp"
#include "trybble.hpp"
#include "tryte.hpp"

namespace termite
{
    const Tryte Tryte::MINUS_ONE(from_bct, 0b00'00'00'00'00'00);
    const Tryte Tryte::ZERO(from_bct, 0b00'00'00'00'00'01);
    const Tryte Tryte::ONE(from_bct, 0b00'00'00'00'00'10);

    Tryte::Tryte(FromBCT, uint16_t bct)
        : bct(bct) {
    }

    Tryte::Tryte(FromVal, int16_t val)
        : Tryte(Trybble(from_val, baldiv(val, 27)), Trybble(from_val, balmod(val, 27))) {
    }

    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : bct((hi.bct << 6) + lo.bct) {
    }

    Tryte Tryte::operator-() const {
        return operator~();
    }

    Tryte Tryte::operator+(const Tryte& other) const {
        // BCT addition algorithm based on https://homepage.cs.uiowa.edu/~dwjones/bcd/bcd.html

        uint16_t a = bct;
        uint16_t b = other.bct;

        uint16_t t1 = a + 0b01'01'01'01'01'01;
        uint16_t t2 = t1 + b;
        uint16_t t3 = t1 ^ b;
        uint16_t t4 = t2 ^ t3;
        uint16_t t5 = ~t4 & 0b10'10'10'10'10'100;
        uint16_t t6 = (t5 >> 2);
        uint16_t t7 = 0b10'10'10'10'10'10 - (t2 - t6);

        return Tryte(from_bct, t7);
    }


    Tryte Tryte::operator-(const Tryte& other) const {
        return operator+(-other);
    }

    Tryte Tryte::operator*(const Tryte& other) const {
        // Naive implementation that converts to native integer and back
        // This implementation will remain until I find an algorithm for BCT multiplication

        return Tryte(from_val, balmod(to_int16_t() * other.to_int16_t(), 729));
    }

    Tryte Tryte::operator/(const Tryte& other) const {
        // Naive implementation that converts to native integer and back
        // This implementation will remain until I find an algorithm for BCT division

        return Tryte(from_val, to_int16_t() / other.to_int16_t());
    }

    Tryte Tryte::operator~() const {
        return Tryte(from_bct, 0b10'10'10'10'10'10 - bct);
    }

    Tryte Tryte::operator&(const Tryte& other) const {
        return Tryte(hi_trybble() & other.hi_trybble(), lo_trybble() & other.lo_trybble());
    }

    Tryte Tryte::operator|(const Tryte& other) const {
        return Tryte(hi_trybble() | other.hi_trybble(), lo_trybble() | other.lo_trybble());
    }

    Tryte Tryte::operator^(const Tryte& other) const {
        return Tryte(hi_trybble() ^ other.hi_trybble(), lo_trybble() ^ other.lo_trybble());
    }

    int16_t Tryte::to_int16_t() const {
        return hi_trybble().to_int8_t() * 27 + lo_trybble().to_int8_t();
    }

    std::string Tryte::to_ternary_str() const {
        return hi_trybble().to_ternary_str() + lo_trybble().to_ternary_str();
    }

    std::string Tryte::to_hept_str() const {
        return std::string() + hi_trybble().to_hept_digit() + lo_trybble().to_hept_digit();
    }

    bool Tryte::is_neg() const {
        return bct < 0b01'01'01'01'01;
    }

    Trybble Tryte::hi_trybble() const {
        return Trybble(from_bct, bct >> 6);
    }

    Trybble Tryte::lo_trybble() const {
        return Trybble(from_bct, bct & 63);
    }
} // namespace termite