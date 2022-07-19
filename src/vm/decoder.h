#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <array>

#include "../core/trit.h"
#include "word.h"
#include "op.h"
#include "instr.h"

namespace termite
{
    // Decodes a 4-trit opcode into the corresponding operation
    Op decode_op(const std::array<Trit, 4> &opcode);

    // Decodes an 18-trit block of data into the corresponding CPU instruction
    Instr decode_instr(const std::array<Trit, 18> &trits);
} // namespace termite

#endif