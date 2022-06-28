#ifndef TRIT_H
#define TRIT_H

namespace termite
{
    // Ternary analogue to a bit. Represents a value of -1, 0, or 1.
    class Trit
    {
    public:
        // Restricted to 2 bits to remove unnecessary space
        int val : 2;

        // Creates a trit equal to 0
        Trit();

        // Creates a trit from a native integer
        Trit(int val);

        // Creates a trit from a character
        Trit(char chr);

        // Returns a clone of the trit
        Trit clone() const;

        // Returns the logical AND of two trits in Kleene logic
        Trit operator&&(const Trit &other) const;

        // Returns the logical OR of two trits in Kleene logic
        Trit operator||(const Trit &other) const;

        // Returns the logical XOR of two trits in Kleene logic
        Trit operator^(const Trit &other) const;

        // Returns the logical NOT of the trit in Kleene logic
        Trit operator!() const;

        // Returns a character representation of the trit for printing/debugging
        char to_chr() const;

        // A trit with a value of -1
        static const Trit MINUS_ONE;

        // A trit with a value of 0
        static const Trit ZERO;

        // A trit with a value of 1
        static const Trit ONE;
    };
} // namespace termite

#endif