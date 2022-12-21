#ifndef TRIT_H
#define TRIT_H

#include <utility>

namespace termite
{
    // Ternary bit that can hold the value 0, 1, or 2
    class Trit {
    private:
        int val = 0;
    public:
        Trit() = default;

        // Convert an int to a trit
        Trit(int val);

        // NOT (defined as in Kleene logic)
        Trit operator~() const;
        
        // AND
        Trit operator&(const Trit& other) const;

        // OR
        Trit operator|(const Trit& other) const;
        
        // XOR
        Trit operator^(const Trit& other) const;

        // Full adder returning a std::pair of the sum and carry
        std::pair<Trit, Trit> full_add(const Trit& other, const Trit& carry_in) const;

        // Convert a trit to int
        int to_int() const;

        // Convert trit to char for printing
        char to_char() const;
    };
} // namespace termite

#endif // TRIT_H