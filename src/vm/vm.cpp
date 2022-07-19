#include <string>
#include <vector>
#include <stack>

#include "../core/duet.h"
#include "../core/tryte.h"
#include "../core/exceptions.h"
#include "word.h"
#include "instr.h"
#include "decoder.h"
#include "vm.h"

namespace termite
{
    void VM::exec_program(const std::vector<Instr> &program)
    {
        for(const Instr &instr : program) 
        {
            switch(instr.op)
            {
            case Op::NOP:
                break;
            case Op::LDA:
                lda(instr.operand, instr.addr_mode);
                break;
            default:
                throw TermiteException("unimplemented");
            }
        }
    }

    void VM::lda(const Word &operand, const Duet &addr_mode)
    {
        switch(addr_mode.to_int())
        {
        case 0:
            accum_reg = mem[operand];
            break;
        case 1:
            accum_reg = operand.hi;
            break;
        default:
            throw TermiteException(std::string("invalid addressing mode: ") + addr_mode.to_chr());
            break;
        }
    }

    void VM::ldx(const Word &operand, const Duet &addr_mode)
    {
        switch(addr_mode.to_int())
        {
        case 0:
            x_reg = mem[operand];
            break;
        case 1:
            x_reg = operand.hi;
            break;
        default:
            throw TermiteException(std::string("invalid addressing mode: ") + addr_mode.to_chr());
            break;
        }
    }
} // namespace termite