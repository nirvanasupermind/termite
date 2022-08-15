// -*- cpu/decoder.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef DECODER_H
#define DECODER_H

#include "../core/tryte.h"
#include "op.h"

namespace termite {
    // Converts an opcode to a member of the Op enum.
    Op decode_opcode(const Tryte &opcode);
}

#endif // DECODER_H