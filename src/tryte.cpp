#include <string>
#include <cinttypes>

#include "util.hpp"
#include "tryte.hpp"

namespace termite {
    Tryte::Tryte(const Trybble &hi, const Trybble &lo)
        : hi(hi), lo(lo) {
    }

    Tryte::Tryte(int16_t num) {
        int16_t quot = num / 27, mod = num % 27;

        if(mod > 13) {
            quot++;
            mod -= 27;
        } else if(mod < -13) {
            quot--;
            mod += 27;
        }

        hi = Trybble(quot);
        lo = Trybble(mod);
    }

    Trybble Tryte::get_hi() const {
        return hi;
    }

    Trybble Tryte::get_lo() const {
        return lo;
    }

    int16_t Tryte::to_int() const {
        return hi.to_int() * 27 + lo.to_int();
    }   

    std::string Tryte::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }   

    std::string Tryte::to_sept_str() const {
        return std::string() + hi.to_sept_digit() + lo.to_sept_digit();
    }   
} // namespace termite