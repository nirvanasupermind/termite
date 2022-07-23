#include "../core/trybble.h"
#include "../core/tryte.h"
#include "op.h"
#include "instr.h"

namespace termite
{
    Instr::Instr(Op op, const Trybble &addr_mode1, const Tryte &addr1, const Trybble &addr_mode2, const Tryte &addr2)
        : op(op), addr_mode1(addr_mode1), addr1(addr1), addr_mode2(addr_mode2), addr2(addr2)
    {
    }
} // namespace termite