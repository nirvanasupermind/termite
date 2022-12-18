#ifndef TRYTE_H
#define TRYTE_H

#include <array>
#include <cinttypes>
#include <string>
#include "trit.h"

namespace termite {
    class Tryte {
    public:
        std::array<Trit, 6> trits;
        Tryte(const std::array<Trit, 6>& trits);
        Tryte(int n);
        Tryte operator-() const;
        Tryte operator+(const Tryte& other) const;
        Tryte operator-(const Tryte& other) const;
        Tryte operator*(const Tryte& other) const;
        Tryte operator/(const Tryte& other) const;
        Tryte operator%(const Tryte& other) const;        
        Tryte operator&(const Tryte& other) const;   
        Tryte operator|(const Tryte& other) const;
        Tryte operator^(const Tryte& other) const;
        int to_int() const;
        std::string to_string() const;
    };
} // namespace termite

#endif // TRIT_H