
#ifndef WORD_H
#define WORD_H

#include <cstdint>
#include <string>
#include <utility>

#include "tryte.h"

namespace termite {
    const int TRITS_PER_WORD = 16;
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
        Word operator^(const Word& other) const;
        Word operator<<(const Word& other) const;
        Word operator>>(const Word& other) const;
        Word operator+(const Word& other) const;
        std::pair<Word, uint8_t> add_with_carry(const Word& other) const;
        Word operator-(const Word& other) const;
        std::pair<Word, uint8_t> sub_with_carry(const Word& other) const;
        Word operator*(const Word& other) const;
        // bool operator<(const Word& other) const;
        int32_t to_int32() const;
        std::string to_ternary_str() const;
        // I did not want to use wchar because it is platform-specific
        // But char is only 8 bits, char16_t can't be printed
        static Word from_int32(int32_t n);
        static Word from_ternary_str(const std::string& s);
    };

} // namespace termite

#endif
