#include "tryte.h"
#include "instr.h"

namespace termite
{
    Instr::Instr(InstrType type, const Tryte &op1, const Tryte &op2)
        : type(type), op1(op1), op2(op2)
    {
    }
} // namespace termite