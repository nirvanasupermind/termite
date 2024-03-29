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


    class Word {
    public:
        static Word from_int16(int16_t n);
        uint16_t bct;
        Word();
        Word(uint16_t bct);
        Word operator-() const;
        Trit get_trit(int i) const;
        void set_trit(int i, const Trit& trit);
        int16_t to_int16() const;
        std::string to_ternary_str() const;
    };
} // namespace termite

#endif // TRYTE_H