#ifndef INSTR_H
#define INSTR_H

#include "../core/trybble.h"
#include "../core/tryte.h"
#include "op.h"

namespace termite
{
    // Represents a machine code instruction executed by the VM.
    // An instruction consists of an operation type, an address, and an addressing mode.

    class Instr 
    {
    public:
        Op op;
        Trybble addr_mode1;
        Tryte addr1;
        Trybble addr_mode2;
        Tryte addr2;
        Instr(Op op, const Trybble &addr_mode1, const Tryte &addr1, const Trybble &addr_mode2, const Tryte &addr2); 
    };
} // namespace termite

#endif