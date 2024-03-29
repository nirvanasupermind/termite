// Class for words (16-trit integer)

#ifndef WORD_H
#define WORD_H

#include <cinttypes>
#include <string>
#include <utility>
#include "trit.h"
#include "tryte.h"

namespace termite {
    const int WORD_TRIT = 16;
    const int WORD_MAX = 43046721;
    
    class Word {
    public:
        static Word from_int32(int32_t n);
        uint32_t bct;
        Word();
        Word(uint32_t bct);
        Trit get_trit(int i) const;
        Word get_trit_range(int start, int width) const;
        void set_trit(int i, const Trit& trit);
        Word operator-() const;
        std::pair<Word, Trit> operator+(const Word& other) const;
        std::pair<Word, Trit> operator-(const Word& other) const;
        Word operator*(const Word& other) const;
        Word operator~() const;
        Word operator&(const Word& other) const;
        Word operator|(const Word& other) const;
        Word operator>>(int shift) const;
        Word operator<<(int shift) const;
        int32_t to_int32() const;
        std::string to_ternary_str() const;
        std::string to_nonary_str() const;
        Word lo_tryte() const;
        Word hi_tryte() const;
    };
} // namespace termite

#endif // WORD_H