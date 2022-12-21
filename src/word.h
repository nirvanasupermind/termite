#ifndef WORD_H
#define WORD_H

#include <cinttypes>
#include <string>
#include "trit.h"
#include "tryte.h"
#include "word.h"

namespace termite
{
    // 12-trit unbalanced ternary integer type, efficiently packed using binary-coded ternary
    // This is the main numeric type used in the VM
    class Word {
    private:
        uint32_t bct = 0;
    public:
        static const int MAX = 531441;

        Word() = default;

        // Converts binary-coded-ternary data to a word
        Word(uint32_t bct);

        // Convert an int to a word
        static Word from_int(int val);

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

        // Add
        Word operator+(const Word& other) const;

        // Subtract
        Word operator-(const Word& other) const;

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
        
        // Convert a word to a ternary string for printing
        std::string to_ter_string() const;

        // Convert a word to a septemvigesimal (base 27) string for printing
        std::string to_sep_string() const;
    };
} // namespace termite

#endif // WORD_H