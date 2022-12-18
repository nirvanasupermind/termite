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
        Trit operator^(const Trit& other) const;
        std::pair<Trit, Trit> full_add(const Trit& other, const Trit &carry) const;
        char to_char() const;
    };
} // namespace termite

#endif // TRIT_H