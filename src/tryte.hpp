#if !defined(TRYTE_HPP)
#define TRYTE_HPP

#include <string>
#include <cinttypes>

#include "tryte.hpp"

namespace termite {
    // 6-trit balanced ternary integer type with values from -364 through 364
    // Implemented using binary-coded ternary (BCT) representation, where each trit is encoded by 2 bits

    class Tryte {
    public:
        // Default constructor
        Tryte();

        // Creates a tryte from it's high and low trytes
        Tryte(const Trybble& hi, const Trybble& lo);

        // Creates a tryte from a native integer
        Tryte(int16_t num);

        // Returns the tritwise NOT of a tryte
        Tryte operator~() const;

        // Returns the tritwise AND of two trytes
        Tryte operator&(const Tryte& other) const;

        // Returns the tritwise OR of two trytes
        Tryte operator|(const Tryte& other) const;

        // Returns the high trybble of a tryte
        Trybble get_hi() const;

        // Returns the low trybble of a tryte
        Trybble get_lo() const;

        // Returns a native integer representation of a tryte
        int16_t to_int() const;

        // Returns a ternary string representation of a tryte
        std::string to_ternary_str() const;

        // Returns a septemvigesimal (base 27) string representation of a tryte
        std::string to_sept_str() const;
    protected:
        Trybble hi;

        Trybble lo;
    };
} // namespace termite

#endif // TRYTE_HPP