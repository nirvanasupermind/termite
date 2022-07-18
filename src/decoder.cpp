#include <string>

#include "instr.h"
#include "decoder.h"
#include "exceptions.h"

namespace termite
{
    Op decode_instr(const Tryte &opcode)
    {
        // Unimplemented

        // Old implementation:
        // switch (opcode.to_int())
        // {
        // case 0:
        //     return Op::NOP;
        // case 1:
        //     return Op::LDA;  
        // case 2:
        //     return Op::STA;
        // case 3:
        //     return Op::LDX;

        // case 5:
        //     return Op::OUT;
        // case 6:
        //     return Op::ADD;
        // case 7:
        //     return Op::NEG;
        // case 8:
        //     return Op::SUB;
        // case 9:
        //     return Op::MUL;
        // case 10:
        //     return Op::SHL;
        // case 11:
        //     return Op::SHR;
        // case 12:
        //     return Op::CMP;
        // case 13:
        //     return Op::JMP;
        // case 14:
        //     return Op::JE;
        // case 15:
        //     return Op::JNE;
        // case 16:
        //     return Op::JL;
        // case 17:
        //     return Op::JG;
        // case 18:
        //     return Op::JLE;
        // case 19:
        //     return Op::JGE;
        // default:
        //     throw TermiteException("illegal instruction: " + opcode.to_str());
        // }
    }
} // namespace termite