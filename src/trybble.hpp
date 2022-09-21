// -*- trybble.hpp -*-
// Part of the Termite project, under the MIT License.

#if !defined(TRYBBLE_HPP)
#define TRYBBLE_HPP

#include <string>
#include <cinttypes>

#include "util.hpp"

namespace termite {
    // 3-trit balanced ternary integer type with values values from -13 through 13
    // Implemented using binary-coded ternary (BCT) representation, where each trit is encoded by 2 bits

    class Trybble {
    public:
        // Default constructor
        Trybble();
        
        // Creates a trybble from it's BCT encoding
        Trybble(FromBCT, uint8_t bct);

        // Creates a trybble from a native integer
        Trybble(int8_t num);

        // Returns the tritwise NOT of a trybble
        Trybble operator~() const;

        // Returns the tritwise AND of two trybbles
        Trybble operator&(const Trybble &other) const;

        // Returns the tritwise OR of two trybbles
        Trybble operator|(const Trybble &other) const;

        // Returns the BCT encoding of a trybble
        uint8_t get_bct() const;

        // Returns a native integer representation of a trybble
        int8_t to_int() const;

        // Returns a ternary string representation of a trybble
        std::string to_ternary_str() const;

        // Returns a septemvigesimal (base 27) digit representation of a trybble
        char to_sept_digit() const;
    protected:
        uint8_t bct;
    };
} // namespace termite


#endif // TRYBBLE_HPP