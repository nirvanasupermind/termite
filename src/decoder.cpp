#include <string>
#include <exception>

#include "decoder.h"
#include "tryte.h"
#include "instr.h"

namespace termite
{
    const char *DecodeError::what() const noexcept
    {
        return msg.c_str();
    }

    InstrOp decodeOp(const Tryte &op)
    {
        std::string str = op.str();

        if (str == "000000")
        {
            return InstrOp::NOP;
        }

        if (str == "000001")
        {
            return InstrOp::PUSH;
        }

        if (str == "00001N")
        {
            return InstrOp::POP;
        }

        if (str == "000010")
        {
            return InstrOp::SWAP;
        }

        if (str == "000011")
        {
            return InstrOp::SYSCALL;
        }

        if (str == "0001TT")
        {
            return InstrOp::ADD;
        }

        if (str == "0001T0")
        {
            return InstrOp::MUL;
        }

        if (str == "0001T1")
        {
            return InstrOp::NEG;
        }

        if (str == "00010T")
        {
            return InstrOp::AND;
        }

        if (str == "000100")
        {
            return InstrOp::OR;
        }

        if (str == "000101")
        {
            return InstrOp::XOR;
        }

        if (str == "00011T")
        {
            return InstrOp::NOT;
        }

        throw DecodeError("illegal instruction " + op.str());

        return InstrOp::NOP;
    }

    Instr decodeInstr(const Word &instr)
    {
        InstrOp op = decodeOp(instr.hi);

        Tryte val = instr.lo;
        
        return Instr(op, val);
    }
}