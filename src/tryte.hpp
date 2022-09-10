#if !defined(TRYTE_HPP)
#define TRYTE_HPP

#include <cstdint>
#include <string>
#include <array>

#include "util.hpp"
#include "trybble.hpp"

namespace termite {
    // 6-trit balanced ternary integer type implemented using a binary-coded ternary or BCT data representation
    class Tryte { 
    public:
        // The tryte with a value of -1
        static const Tryte MINUS_ONE;
    
        // The tryte with a value of 0
        static const Tryte ZERO;

        // The tryte with a value of 1
        static const Tryte ONE;

        // The BCT encoding of the tryte
        uint16_t bct;

        /////////////////////////////////////////
        // Constructors
        
        // Creates a tryte from it's BCT encoding
        Tryte(FromBCT, uint16_t bct);

        // Creates a tryte from a native integer
        Tryte(FromVal, int16_t val);
        
        // Creates a tryte from it's high and low trybbles
        Tryte(const Trybble &hi, const Trybble &lo);

        // 3's complement negation
        Tryte operator-() const;
        
        /////////////////////////////////////////
        // Operators

        // Add operator
        Tryte operator+(const Tryte& other) const;

        // Subtract operator
        Tryte operator-(const Tryte& other) const;

        // Multiply operator
        Tryte operator*(const Tryte& other) const;

        // Divide operator
        Tryte operator/(const Tryte& other) const;

        // Tritwise NOT
        Tryte operator~() const;

        // Tritwise AND
        Tryte operator&(const Tryte& other) const;

        // Tritwise OR
        Tryte operator|(const Tryte& other) const;

        // Tritwise XOR
        Tryte operator^(const Tryte& other) const;

        /////////////////////////////////////////
        // Conversion
                
        // Converts a tryte into a native integer
        int16_t to_int16_t() const;

        // Converts a tryte into a ternary string
        std::string to_ternary_str() const;

        // Converts a tryte into a heptavigesimal string
        std::string to_hept_string() const;

        /////////////////////////////////////////
        // Misc

        // Checks if a tryte is negative
        bool is_neg() const;

        // Returns the hi trybble of the tryte
        Trybble hi_trybble() const;

        // Returns the lo trybble of the tryte
        Trybble lo_trybble() const;
    };
} // namespace termite

#endif // TRYTE_HPP