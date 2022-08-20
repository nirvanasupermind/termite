// -*- core/halfword.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef HALFWORD_H
#define HALFWORD_H

#include <string>
#include <cstdint>

#include "util.h"
#include "tryte.h"

namespace termite {
    // A halfword is half of a full 24-trit word, representing 12 trits or 2 trytes of data.
    // Most often, halfwords are used as a numerical data type, with their trits 
    // encoding the ternary representation of a number from -265720 to +265720.
    
    class Halfword {
    public:
        Tryte hi;

        Tryte lo;

        // Creates a BCT halfword equal to 0.
        Halfword() = default;

        // Convert two BCT trytes to a BCT halfword.
        Halfword(const Tryte& hi, const Tryte& lo);

        // Converts raw bits to a BCT halfword.
        Halfword(FromBits, uint16_t bits);

        // Returns the value of the BCT tryte's high trybble.
        int16_t hi_val() const;

        // Returns the value of the BCT tryte's low trybble.
        int16_t lo_val() const;

        // Returns the internal bits of the BCT halfword, stored inside a native uint32.
        uint32_t bits() const;

        // Converts the BCT tryte to a native int16.
        int16_t to_int16() const;

        // Converts the BCT tryte to a native uint16.
        uint16_t to_uint16() const;

        // Returns true if the halfword has a negative value when using 3's complement, and false otherwise.
        bool is_neg() const;

        // Converts the BCT halfword to a ternary string.
        std::string to_ternary_str() const;

        // Returns the sum of two BCT halfwords.
        Tryte operator+(const Tryte& other) const;

        // Returns the negation (3's complement) of the BCT halfword.
        Tryte operator-() const;

        // Returns the difference of two BCT halfwords.
        Tryte operator-(const Tryte& other) const;

        // Returns the product of two BCT halfwords.
        Tryte operator*(const Tryte& other) const;

        // Returns the unsigned product of two BCT halfwords.
        Tryte mulu(const Tryte& other) const;

        // Returns the quotient of two BCT halfwords.
        Tryte operator/(const Tryte& other) const;

        // Returns the unsigned quotient of two BCT halfwords.
        Tryte divu(const Tryte& other) const;

        // Returns the tritwise NOT of the BCT halfword.
        Tryte operator~() const;

        static const Halfword ONE;
    };
} // namespace termite

#endif // TRYTE_H