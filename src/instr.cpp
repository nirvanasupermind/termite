#include "tryte.h"
#include "instr.h"

namespace termite
{
    Instr::Instr(InstrType type, const Tryte &val)
        : type(type), val(val)
    {
    }
} // namespace termite