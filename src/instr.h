#ifndef INSTR_H
#define INSTR_H

#include "duet.h"
#include "tryte.h"
#include "word.h"
#include "op.h"

namespace termite
{

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