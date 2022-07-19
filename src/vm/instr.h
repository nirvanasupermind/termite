#ifndef INSTR_H
#define INSTR_H

#include "../core/duet.h"
#include "word.h"
#include "op.h"

namespace termite
{
    // Represents a machine code instruction executed by the VM.
    // An instruction consists of an operation type, an addressable, and an addressing mode.

    class Instr 
    {
    public:
        Op op;
        Word operand;
        Duet addr_mode;

        Instr(Op op, const Word &operand, const Duet &addr_mode);
    };
} // namespace termite

#endif