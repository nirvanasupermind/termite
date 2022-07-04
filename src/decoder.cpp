#include <string>

#include "instr.h"
#include "decoder.h"
#include "exceptions.h"

namespace termite
{
    InstrType decode_instr_type(const Tryte &tryte)
    {
        switch (tryte.to_int())
        {
        case 0:
            return InstrType::NOP;
        case 1:
            return InstrType::PUSH;
        case 2:
            return InstrType::POP;
        case 3:
            return InstrType::SWAP;
        case 4:
            return InstrType::IN;
        case 5:
            return InstrType::OUT;
        case 6:
            return InstrType::ADD;
        case 7:
            return InstrType::NEG;
        case 8:
            return InstrType::SUB;   
        case 9:
            return InstrType::MUL;
        case 10:
            return InstrType::AND;    
        case 11:
            return InstrType::OR;  
        case 12:
            return InstrType::XOR;
        case 13:
            return InstrType::JMP;      
        case 14:
            return InstrType::JE;
        case 15:
            return InstrType::JNE;
        case 16:
            return InstrType::JL;
        case 17:
            return InstrType::JG;
        case 18:
            return InstrType::JLE;
        case 19:
            return InstrType::JGE;            
        default:
            throw TermiteException("illegal instruction: " + tryte.to_str());
        }
    }

    Instr decode_instr(const Word &word)
    {
        return Instr(decode_instr_type(word.hi), word.lo);
    }
} // namespace termite