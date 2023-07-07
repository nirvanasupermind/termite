// Class for trits (ternary bits), either -1, 0, or 1

#ifndef TRIT_H
#define TRIT_H

#include <cinttypes>
#include <utility>


namespace termite {
    class Trit {
    public:
        int8_t val;
        Trit();
        Trit(int8_t val);
        Trit operator~() const;
        Trit operator&(const Trit& other) const;
        Trit operator|(const Trit& other) const;
        std::pair<Trit, Trit> full_add(const Trit& other, const Trit& carry_in) const;
        char to_char() const;
        bool to_bool() const;
    };
} // namespace termite

#endif // TRYTE_H