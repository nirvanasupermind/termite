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
            return InstrType::POP;
        case 2:
            return InstrType::IN;
        case 3:
            return InstrType::OUT;
        case 4:
            return InstrType::LOAD;
        case 5:
            return InstrType::STOR;
        case 6:
            return InstrType::ADD;
        case 7:
            return InstrType::NEG;
        case 8:
            return InstrType::SUB;
        case 9:
            return InstrType::MUL;
        case 10:
            return InstrType::NOT; 
        case 11:
            return InstrType::AND;  
        case 12:
            return InstrType::OR;
        case 13:
            return InstrType::XOR;
        case 14:
            return InstrType::LS;
        case 15:
            return InstrType::RS;
        case 16:
            return InstrType::CMP;
        case 17:
            return InstrType::JMP;
        case 18:
            return InstrType::CJMP;           
        default:
            throw TermiteException("illegal instruction: " + tryte.to_str());
        }
    }

    Instr decode_instr(const Word &word)
    {
        return Instr(decode_instr_type(word.hi), word.lo);
    }
} // namespace termite