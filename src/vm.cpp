#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "tryte.h"
#include "word.h"
#include "instr.h"
#include "decoder.h"
#include "exceptions.h"
#include "vm.h"

namespace termite
{
    void VM::exec_program(const std::vector<Word> &program)
    {
        for (int i = 0; i < program.size(); i++)
        {
            Instr instr = decode_instr(program.at(i));

            switch (instr.type)
            {
            case InstrType::NOP:
                break;
            case InstrType::MOV:
                mem[instr.op1] = instr.op2;
                break;
            case InstrType::LDA:
                accum = mem[instr.op1];
                break;
            case InstrType::STA:
                mem[instr.op1] = accum;
                break;
            case InstrType::IN:
                mem[instr.op1] = accum;
                break;
            }

        }
    }

    void VM::mov(const Tryte &op1, const Tryte &op2)
    {
        mem[op1] = op2;
    }

    void VM::lda(const Tryte &op1)
    {
        accum = op1;
    }

    void VM::sta(const Tryte &op1)
    {
        accum = op1;
    }

} // namespace termite