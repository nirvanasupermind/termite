#include "util.hpp"

#include <cstdint>

namespace termite
{
    int32_t baldiv(int32_t x, int32_t y) {
        int32_t result = x / y;
        int32_t half_x = x >> 1;

        if(x % y < half_x) {
            return result;
        } else {
            return result + 1;
        }
    }

    int32_t balmod(int32_t x, int32_t y) {
        int32_t result = x % y;
        int32_t half_x = x >> 1;

        if(result < half_x) {
            return result;
        } else {
            return result - half_x;
        }
    }
} // namespace termite