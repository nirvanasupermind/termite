#include "util.hpp"

#include <iostream>
#include <cstdint>

namespace termite
{
    int32_t baldiv(int32_t x, int32_t y) {
        int32_t result = x / y;

        if(x % y < (y >> 1)) {
            return result;
        } else {
            return result + 1;
        }
    }

    int32_t balmod(int32_t x, int32_t y) {
        int32_t result = x % y;

        if(result < (y >> 1)) {
            return result;
        } else {
            return result - y;
        }
    }
} // namespace termite