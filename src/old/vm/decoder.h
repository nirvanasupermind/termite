#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <array>

#include "../core/trit.h"
#include "../core/tryte.h"
#include "op.h"
#include "instr.h"

namespace termite
{
    // Decodes a 4-trit opcode into the corresponding operation
    Op decode_op(const Tryte &opcode);

    // Decodes an 18-trit/3-tryte block of data into the corresponding CPU instruction.
    // The format of a raw ternary instruction is a 4-trit opcode, followed by a 2-trit addressing mode, followed by a 12-trit addressable.

    Instr decode_instr(const Tryte &tryte0, const Tryte &tryte1, const Tryte &tryte2, const Tryte &tryte3 );
} // namespace termite

#endif