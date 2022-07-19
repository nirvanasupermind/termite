#include <string>
#include <array>

#include "../core/trit.h"
#include "../core/tryte.h"
#include "../core/exceptions.h"
#include "instr.h"
#include "decoder.h"

namespace termite
{
    Op decode_op(const std::array<Trit, 4> &opcode)
    {
        int i = opcode.at(0).val * 27 + opcode.at(1).val * 9 + opcode.at(2).val * 3 + opcode.at(3).val * 9;

        if(i <= 26) 
        {
            return (Op)i;
        }

        throw TermiteException("illegal instruction: " + std::string() + opcode.at(0).to_chr() + opcode.at(1).to_chr() + opcode.at(2).to_chr() + opcode.at(3).to_chr());
    }

    Instr decode_instr(const std::array<Trit, 18> &trits) 
    {
        std::array<Trit, 4> opcode {trits.at(0), trits.at(1), trits.at(2), trits.at(3)};

        Op op = decode_op(opcode);

        std::array<Trit, 6> operand_hi_trits {trits.at(4), trits.at(5), trits.at(6), trits.at(7), trits.at(8), trits.at(9)};

        std::array<Trit, 6> operand_lo_trits {trits.at(10), trits.at(11), trits.at(12), trits.at(13), trits.at(14), trits.at(15)};

        Word operand {Tryte(operand_hi_trits), Tryte(operand_lo_trits)};

        Duet addr_mode(trits.at(16), trits.at(17));

        return Instr(op, operand, addr_mode);
    }
} // namespace termite