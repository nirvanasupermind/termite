#include <string>

#include "instr.h"
#include "tryte.h"

namespace termite
{
    Instr::Instr(InstrOp op)
        : op(op)
    {
    }

    Instr::Instr(InstrOp op, Tryte val)
        : op(op), val(val)
    {
    }
}