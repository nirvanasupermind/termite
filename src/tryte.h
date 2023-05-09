// Class for trytes (8-trit integer)

#ifndef TRYTE_H
#define TRYTE_H

#include <cinttypes>
#include <string>
#include "trit.h"

namespace termite {
    const int TRYTE_TRIT = 8;
    const int TRYTE_MAX = 6561;
    const int POW3[16] = { 1, 3, 9, 27, 81, 243, 729, 2187, 6561,
    19683, 59049, 177147, 531441, 1594323, 4782969, 14348907 };


    class Tryte {
    public:
        static Tryte from_int(int n);
        uint16_t bct;
        Tryte();
        Tryte(uint16_t bct);
        Tryte operator-() const;
        Trit get_trit(int i) const;
        void set_trit(int i, const Trit& trit);
        int to_int() const;
        std::string to_ternary_str() const;
    };
} // namespace termite

#endif // TRYTE_H