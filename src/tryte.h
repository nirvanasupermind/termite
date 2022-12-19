#ifndef TRYTE_H
#define TRYTE_H

#include <array>
#include <cinttypes>
#include <string>
#include <utility>
#include "trit.h"

namespace termite {
    class Tryte {
    public:
        std::array<Trit, 6> trits;
        Tryte();
        Tryte(const std::array<Trit, 6>& trits);
        static Tryte from_int(int n);
        static Tryte from_bct(uint16_t bct);
        Tryte operator-() const;
        Tryte operator+(const Tryte& other) const;
        Tryte operator-(const Tryte& other) const;
        Tryte operator*(const Tryte& other) const;
        std::pair<Tryte, Tryte> operator/(const Tryte& other) const;
        Tryte operator&(const Tryte& other) const;   
        Tryte operator|(const Tryte& other) const;
        Tryte operator^(const Tryte& other) const;
        Tryte operator>>(int amount) const;
        Tryte operator<<(int amount) const;
        int to_int() const;
        uint16_t to_bct() const;
        std::string to_string() const;
    };
} // namespace termite

#endif // TRIT_H