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
    Tryte VM::pop_val() 
    {
        if(stack.size() == 0)
        {
            throw TermiteException("pop from empty stack");
        }

        Tryte result = stack.top();
        stack.pop();
        return result;
    }

    void VM::exec_program(const std::vector<Word> &program)
    {
        for (int i = 0; i < program.size(); i++)
        {
            Instr instr = decode_instr(program.at(i));

            switch (instr.type)
            {
            case InstrType::NOP:
                break;
            case InstrType::PUSH:
                push(instr.val);
                break;
            case InstrType::POP:
                pop();
                break;
            case InstrType::SWAP:
                swap();
                break;
            case InstrType::IN:
                in(instr.val);
                break;
            case InstrType::OUT:
                out(instr.val);
                break;
            case InstrType::ADD:
                add();
                break;
            case InstrType::SUB:
                sub();
                break;
            case InstrType::MUL:
                mul();
                break;
            case InstrType::AND:
                and_();
                break;
            case InstrType::OR:
                or_();
                break;
            case InstrType::XOR:
                xor_();
                break;
            case InstrType::JMP:
                i = instr.val.to_int();
                continue;
            default:
                throw std::string("unimplented instruction: " + std::to_string((int)instr.type));
                break;
            }
        }
    }

    void VM::push(const Tryte &val)
    {
        stack.push(val);
    }

    void VM::pop()
    {
        stack.pop();
    }

    void VM::swap()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(y);
        stack.push(x);
    }

    void VM::in(const Tryte &mode)
    {
        switch (mode.to_int())
        {
        case 1:
        {
            std::string str;
            std::getline(std::cin, str);
            stack.push(Tryte(str));
            break;
        }
        default:
            throw TermiteException("illegal input mode: " + mode.to_str());
        }
    }

    void VM::out(const Tryte &mode)
    {
        switch (mode.to_int())
        {
        case 1:
        {
            std::cout << pop_val().to_str() << '\n';
            break;
        }
        default:
            throw TermiteException("illegal output mode: " + mode.to_str());
        }
    }

    void VM::add()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x + y);
    }

    void VM::neg()
    {
        stack.push(-pop_val());
    }

    void VM::sub()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x - y);
    }

    void VM::mul()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x * y);
    }

    void VM::and_()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x & y);
    }

    void VM::or_()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x | y);
    }

    void VM::xor_()
    {
        Tryte y = pop_val();
        Tryte x = pop_val();
        stack.push(x ^ y);
    }
} // namespace termite