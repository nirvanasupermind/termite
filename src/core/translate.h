//-*- core/translate.h -*-/
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <string>
#include <cstdint>

#include "trybble.h"

namespace termite
{
    // Converts a trybble to a native integer.
    int8_t trybble_to_int8(Trybble trybble);

    // Converts a native integer to a trybble.
    Trybble int8_to_trybble(int8_t val);

    // Converts a trybble to a balanced ternary string.
    std::string trybble_to_ternary_str(Trybble trybble);
} // namespace termite

#endif // TRYBBLE_H