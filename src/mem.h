#ifndef MEM_H
#define MEM_H

#include <array>
#include <cinttypes>
#include "tryte.h"

namespace termite {
    const int MAX_MEM = 531441;

    class Mem {
    public:
        std::array<uint16_t, MAX_MEM> data;
    };
} // namespace termite

#endif // TRIT_H