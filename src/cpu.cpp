#include <iostream>
#include <string>
#include <vector>
#include <stack>

#include "cpu.h"
#include "tryte.h"
#include "word.h"
#include "instr.h"
#include "text.h"

namespace termite
{
    void CPU::push(const Tryte &val)
    {
        stack.push(val);
    }

    void CPU::pop()
    {
        stack.pop();
    }

    void CPU::swap()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a);
        stack.push(b);
    }

    void CPU::syscall(const Tryte &val)
    {
        std::string syscall = val.str();

        if (syscall == "000000")
        {
            std::wcout << decodeChar(stack.top().str()) << '\n';
        }
        else if (syscall == "000001")
        {
            std::cout << stack.top().str() << '\n';
        }
        else if (syscall == "00001T")
        {
            std::cout << stack.top().intVal() << '\n';
        }
    }

    void CPU::add()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a + b);
    }

    void CPU::sub()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a - b);
    }

    void CPU::mul()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a * b);
    }

    void CPU::neg()
    {
        Tryte a = stack.top();
        stack.pop();

        stack.push(-a);
    }

    void CPU::and_()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a & b);
    }

    void CPU::or_()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a | b);
    }

    void CPU::xor_()
    {
        Tryte a = stack.top();
        stack.pop();
        Tryte b = stack.top();
        stack.pop();

        stack.push(a ^ b);
    }

    void CPU::not_()
    {
        Tryte a = stack.top();
        stack.pop();

        stack.push(~a);
    }
}