#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "cpu.h"
#include "tryte.h"
#include "word.h"
#include "instr.h"
#include "decoder.h"

namespace termite
{
    void CPU::executeProgram(const std::vector<Word> &program)
    {
        for (int i = 0; i < program.size(); i++)
        {
            executeInstr(decodeInstr(program.at(i)));
        }
    }

    void CPU::executeInstr(const Instr &instr)
    {
        if (instr.op == InstrOp::NOP)
        {
            // Do nothing
        }

        if (instr.op == InstrOp::PUSH)
        {
            stack.push(instr.val);

            return;
        }

        if (instr.op == InstrOp::POP)
        {
            stack.pop();

            return;
        }

        if (instr.op == InstrOp::SWAP)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a);
            stack.push(b);

            return;
        }

        if (instr.op == InstrOp::SYSCALL)
        {
            std::string syscall = instr.val.str();

            if (syscall == "000000")
            {
                std::wcout << decodeChar(stack.top().str()) << '\n';
            }
            else if(syscall == "000001")
            {
                std::cout << stack.top().str() << '\n';
            }
            else if(syscall == "00001T")
            {
                std::cout << stack.top().intVal() << '\n';
            }

            return;
        }

        if (instr.op == InstrOp::ADD)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a + b);

            return;
        }

        if (instr.op == InstrOp::SUB)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a - b);

            return;
        }

        if (instr.op == InstrOp::MUL)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a * b);

            return;
        }

        if (instr.op == InstrOp::NEG)
        {
            Tryte a = stack.top();
            stack.pop();

            stack.push(-a);

            return;
        }

        if (instr.op == InstrOp::AND)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a & b);

            return;
        }

        if (instr.op == InstrOp::OR)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a | b);

            return;
        }

        if (instr.op == InstrOp::XOR)
        {
            Tryte a = stack.top();
            stack.pop();
            Tryte b = stack.top();
            stack.pop();

            stack.push(a ^ b);

            return;
        }

        if (instr.op == InstrOp::NOT)
        {
            Tryte a = stack.top();
            stack.pop();

            stack.push(~a);

            return;
        }
    }
}