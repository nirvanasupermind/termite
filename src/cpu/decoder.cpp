// -*- cpu/decoder.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include "../core/tryte.h"
#include "op.h"
#include "decoder.h"

namespace termite {
    Op decode_opcode(const Tryte &opcode) {
        return (Op)(opcode.to_uint16());
    }
}
