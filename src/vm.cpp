#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <tuple>

#include "tryte.h"
#include "word.h"
#include "instr.h"
#include "vm.h"
#include "exceptions.h"

namespace termite
{
    void VM::nop()
    {
    }

    void VM::pop()
    {
        stack.pop();
    }

    void VM::in(const Tryte &mode)
    {
        switch (mode.to_int())
        {
        case 1:
        // 1 - Input balanced ternary string
        {
            std::string inp;
            std::getline(std::cin, inp);
            stack.push(Tryte(inp));
            break;
        }
        default:
            throw TermiteException("illegal input mode: " + mode.to_str());
        }
    }

    void VM::out()
    {
        Tryte mode = stack.top();
        stack.pop();

        Tryte val = stack.top();
        stack.pop();
        
        switch (mode.to_int())
        {
        case 0:
            // 0 - Output character
            std::cout << (char)(val.to_int());
            break;
        case 1:
            // 1 - Output balanced ternary string
            std::cout << val.to_str();
            break;
        case 2:
            // 2 - Output decimal string
            std::cout << val.to_int();        
            break;
        default:
            throw TermiteException("illegal output mode: " + mode.to_str());
        }
    }

    void VM::load()
    {
        int x;

        std::tie(x, y, z) = my_obj;
        stack.push(mem[addr]);
    }

    void VM::stor(const Tryte &addr)
    {
        mem[addr] = stack.top();
        stack.pop();
    }  

    void VM::add()
    {
        Tryte x = stack.top();
        stack.pop();
        Tryte y = stack.top();
        stack.pop();
        stack.push(x + y);
    }   

    void VM::neg()
    {
        Tryte x = stack.top();
        stack.pop();
        stack.push(-x);
    }   

    void VM::sub()
    {
        Tryte x = stack.top();
        stack.pop();
        Tryte y = stack.top();
        stack.pop();
        stack.push(x - y);
    }   

    void VM::mul()
    {
        Tryte x = stack.top();
        stack.pop();
        Tryte y = stack.top();
        stack.pop();
        stack.push(x * y);
    }   
} // namespace termite