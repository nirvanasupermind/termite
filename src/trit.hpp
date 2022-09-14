#if !defined(TRIT_HPP)
#define TRIT_HPP

#include <cinttypes>
#include <string>

#include "util.hpp"

namespace termite {
    // A ternary digit that can store a value of -1, 0, and 1
    // Supports Kleene logic operations (analogous to binary Boolean logic)

    class Trit {
    public:
        // Constants for trits with values of -1, 0, and 1
        static const Trit MINUS, ZERO, ONE;

        // Creates a trit from it's numeric value 
        Trit(FromBCT, uint8_t bct);

        // Creates a trit from a native integer
        Trit(FromVal, int8_t val);

        // Returns the logical NOT of a trit
        Trit operator!() const;

        // Returns the logical AND of two trits
        Trit operator&&(const Trit &other) const;

        // Returns the logical OR of two trits
        Trit operator||(const Trit &other) const;

        // Returns a native integer representing the trit
        uint8_t to_native_int() const;

        // Returns a balanced ternary digit representing the trit 
        char to_ternary_digit() const;
    protected:
        // The BCT value of the trit
        uint8_t bct;
    };
} // namespace termite

#endif // TRIT_HPPs