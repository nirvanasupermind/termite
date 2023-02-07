#ifndef WORD_H
#define WORD_H

#include <cinttypes>
#include <string>
#include <utility>
#include "trit.h"
#include "tryte.h"
#include "word.h"

namespace termite
{
    // This is the main numeric type used in the VM
    class Word {
    private:
        uint32_t bct = 0;
    public:
        static const Word ZERO;
        static const Word ONE;
        static const int MAX = 531441;
        Word() = default;

        // Converts binary-coded-ternary data to a word
        Word(uint32_t bct);

        // Convert an int to a word
        static Word from_int(int val);

        static Word from_trytes(const Tryte& hi, const Tryte& lo);

        // Get a trit from a word
        Trit get_trit(int idx) const;

        // Set a trit in a word
        void set_trit(int idx, const Trit& val);

        // Get high 6 trits of a word
        Tryte hi_tryte() const;

        // Get low 6 trits of a word
        Tryte lo_tryte() const;

        // Check if a word is negative
        bool is_neg() const;

        // Negate
        Word operator-() const;

        // Add with carry
        std::pair<Word, Trit> operator+(const Word& other) const;

        // Subtract with borrow
        std::pair<Word, Trit> operator-(const Word& other) const;

        // Multiply
        Word operator*(const Word& other) const;
    
        // Unsigned divide with remainder
        std::pair<Word, Word> udiv(const Word& other) const;

        // Signed divide with remainder
        std::pair<Word, Word> sdiv(const Word& other) const;

        // NOT
        Word operator~() const;

        // AND
        Word operator&(const Word& other) const;

        // OR
        Word operator|(const Word& other) const;
        
        // XOR
        Word operator^(const Word& other) const;
        
        // Shift left
        Word operator>>(int amount) const;

        // Logical shift right
        Word lsr(int amount) const;

        // Arithmetic shift right
        Word asr(int amount) const;

        // Convert a word to an int
        int to_int() const;
        
        std::string to_ter_string() const;

        // Convert a word to a nonary (base 9) string for printing
        std::string to_non_string() const;
    };
} // namespace termite

#endif // WORD_H