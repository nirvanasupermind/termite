#include <string>

#include "instr.h"
#include "decoder.h"
#include "exceptions.h"

namespace termite
{
    Instr decode_instr(const Tryte &opcode)
    {
        switch (opcode.to_int())
        {
        case 0:
            return Instr::NOP;
        case 1:
            return Instr::MOV;
        case 2:
            return Instr::LDA;  
        case 3:
            return Instr::STA;
        case 4:
            return Instr::IN;
        case 5:
            return Instr::OUT;
        case 6:
            return Instr::ADD;
        case 7:
            return Instr::NEG;
        case 8:
            return Instr::SUB;
        case 9:
            return Instr::MUL;
        case 10:
            return Instr::SHL;
        case 11:
            return Instr::SHR;
        case 12:
            return Instr::CMP;
        case 13:
            return Instr::JMP;
        case 14:
            return Instr::JE;
        case 15:
            return Instr::JNE;
        case 16:
            return Instr::JL;
        case 17:
            return Instr::JG;
        case 18:
            return Instr::JLE;
        case 19:
            return Instr::JGE;
        default:
            throw TermiteException("illegal instruction: " + opcode.to_str());
        }
    }
} // namespace termite