#include <string>
#include <array>

#include "../core/trit.h"
#include "../core/tryte.h"
#include "../core/exceptions.h"
#include "instr.h"
#include "decoder.h"

namespace termite
{
    Op decode_op(const Tryte &opcode)
    {
        int i = opcode.to_int();

        if(i <= 26) 
        {
            return (Op)i;
        }

        throw TermiteException("illegal instruction: " + opcode.to_int());
    }

    Instr decode_instr(const Tryte &tryte0, const Tryte &tryte1, const Tryte &tryte2, const Tryte &tryte3)
    {
        // opcode = tryte0

        Op op = decode_op(tryte0);

        Trybble addr_mode1 = tryte1.hi_trybble();
                
        Tryte addr1(tryte1.lo_trybble(), tryte2.hi_trybble());

        Trybble addr_mode2 = tryte2.lo_trybble();

        // addr2 = tryte3
                
        return Instr(op, addr_mode1, addr1, addr_mode2, tryte3);
    }

} // namespace termite