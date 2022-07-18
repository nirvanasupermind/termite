#include "duet.h"
#include "word.h"
#include "op.h"
#include "instr.h"

namespace termite
{
    Instr::Instr(Op op, const Word &operand, const Duet &addr_mode)
        : op(op), operand(operand), addr_mode(addr_mode)
    {
    }
} // namespace termite