#if !defined(UTIL_HPP)
#define UTIL_HPP

#include <cstdint>

namespace termite {
    enum FromBCT { from_bct };
    enum FromVal { from_val };

    // "Balanced" division of two native integers
    int32_t baldiv(int32_t x, int32_t y);

    // "Balanced" modulo of two native integers
    int32_t balmod(int32_t x, int32_t y);
} // namespace termite


#endif // UTIL_HPP