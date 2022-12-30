#ifndef TRYTE_H
#define TRYTE_H

#include <cinttypes>
#include <string>
#include "trit.h"

namespace termite
{
    // 6-trit unbalanced ternary integer type, efficiently packed using binary-coded ternary
    class Tryte {
    private:
        uint16_t bct = 0;
    public:
        static const int MAX = 729;

        Tryte() = default;

        // Converts binary-coded-ternary data to a tryte
        Tryte(uint32_t bct);

        // Convert an int to a tryte
        static Tryte from_int(int val);

        // Get a trit from a tryte
        Trit get_trit(int i) const;

        // Set a trit in a tryte
        void set_trit(int i, const Trit& val);

        // Convert tryte to an int
        int to_int() const;    

        // Convert a tryte to a ternary string for printing
        std::string to_ter_string() const;

        // Convert a tryte to a nonary (base 9) string for printing
        std::string to_non_string() const;
    };
} // namespace termite

#endif // TRYTE_H