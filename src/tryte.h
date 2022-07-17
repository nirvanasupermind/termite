#ifndef TRYTE_H
#define TRYTE_H

#include <string>
#include <array>

#include "trit.h"
#include "duet.h"

namespace termite
{
    // Ternary analogue to a byte. 6 trits, a total of 729 states (-364 through 364).
    class Tryte
    {
    protected:
        // The tryte's constituent 6 trits
        std::array<Trit, 6> trits;

        // int mod3(int val);

        // std::array<Trit, 6> to_bt(int val);
    public:
        // Creates a tryte equal to 0
        Tryte() = default;

        // Creates a tryte from it's constituent 6 trits
        Tryte(const std::array<Trit, 6> &trits);

        // Creates a tryte from a native integer
        Tryte(int val);

        // Creates a tryte from a balanced nonary string
        Tryte(const std::string &str);

        // Returns a clone of the tryte
        Tryte clone() const;

        // Returns the negation of the tryte
        Tryte operator-() const;

        // Returns the sum of two trytes
        Tryte operator+(const Tryte &other) const;

        // Returns the difference of two trytes
        Tryte operator-(const Tryte &other) const;
 
        // Returns the product of two trytes
        Tryte operator*(const Tryte &other) const;
 
        // Returns the trit-wise AND of two trytes
        Tryte operator&(const Tryte &other) const;
 
        // Returns the trit-wise OR of two trytes
        Tryte operator|(const Tryte &other) const;
 
        // Returns the trit-wise XOR of two trytes
        Tryte operator^(const Tryte &other) const;
 
        // Returns the tryte shifted to the left
        Tryte operator<<(int amount) const;

        // Returns the tryte shifted to the right
        Tryte operator>>(int amount) const;

        // Returns 1 if the first tryte is greater, -1 if the second tryte is greater, and 0 otherwise
        Trit cmp(const Tryte &other) const;

        // Checks if the two trytes are not equal
        bool operator!=(const Tryte &other) const;

        // Returns the first duet of the tryte
        Duet hi_duet() const;

        // Returns the second duet of the tryte
        Duet mid_duet() const;

        // Returns the third duet of the tryte
        Duet lo_duet() const;
        
        // Returns a native integer representation of the tryte
        int to_int() const;
        
        // Returns a balanced nonary string representation of the tryte for printing/debugging
        std::string to_str() const;

        // A tryte with a value of -1
        static const Tryte MINUS_ONE;

        // A tryte with a value of 0
        static const Tryte ZERO;

        // A tryte with a value of 1
        static const Tryte ONE;
        
        class HashFunction
        {
        public:
            size_t operator()(const Tryte &tryte) const;
        };
    };
} // namespace termite

#endif