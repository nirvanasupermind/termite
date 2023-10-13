
#ifndef WORD_H
#define WORD_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"

namespace termite {
    const int TRITS_PER_WORD = 16;
    const int32_t POW3[TRITS_PER_WORD] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907 };
    // Trit gate lookup tables
    // Note that this is using the BCT encodings of the trits (0b00,0b01, 0b10 or 0,1,2) 
    // rather than actual values (-1,0,1)
    const uint8_t TRIT_NOT[3] = { 2,1,0 };
    const uint8_t TRIT_AND[3][3] = { {0,0,0},{0,1,1},{0,1,2} };
    const uint8_t TRIT_OR[3][3] = { {0,1,2},{1,1,2},{2,2,2} };
    const uint8_t TRIT_SUM[3][3][3] = { {{1,2,0},{2,0,1},{0,1,2}},{{2,0,1},{0,1,2},{1,2,0}},{{0,1,2},{1,2,0},{2,0,1}} };
    const uint8_t TRIT_CARRY[3][3][3] = { {{0,0,1},{0,1,1},{1,1,1}},{{0,1,1},{1,1,1},{1,1,2}},{{1,1,1},{1,1,2},{1,2,2}} };

    class Word {
    protected:
        uint32_t bct;
    public:
        static const Word ONE;
        static const Word TWO;
        Word();
        Word(uint32_t bct);
        Word(const Tryte& lo, const Tryte& hi);
        uint32_t get_bct() const;
        uint8_t get_bct_trit(int i) const;
        void set_bct_trit(int i, uint8_t val);
        Word get_trit_range(int start, int end) const;
        Tryte get_lo_tryte() const;
        Tryte get_hi_tryte() const;
        // NOT is also same as negation
        Word operator~() const;
        Word operator&(const Word& other) const;
        Word operator|(const Word& other) const;
        Word operator<<(const Word& other) const;
        Word operator>>(const Word& other) const;
        Word operator+(const Word& other) const;
        std::pair<Word, uint8_t> add_with_carry(const Word& other) const;
        Word operator-(const Word& other) const;
        std::pair<Word, uint8_t> sub_with_carry(const Word& other) const;
        Word operator*(const Word& other) const;
        bool operator<(const Word& other) const;
        std::string str() const;
        int32_t to_int32() const;
        static Word from_int32(int32_t n);
    };

} // namespace termite

#endif
