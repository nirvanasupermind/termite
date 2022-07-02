#ifndef VM_H
#define VM_H

#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

#include "tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    // Represents the virtual machine that can execute Termite assembly programs
    class VM 
    {
    protected:
        std::unordered_map<Tryte, Tryte, Tryte::HashFunction> mem;
        std::stack<Tryte> stack;
    public:
        VM() = default;
        
        // Do nothing
        void nop();

        // Push tryte to stack
        void pop();        

        // Pop top tryte from stack
        void pop();        

        // Input a tryte in specified mode and push it to stack
        void in();

        // Pop top tryte from stack and output it in specified mode
        void out();

        // Load tryte from specified address in memory and push it to stack
        void load(); 

        // Pop top tryte from stack, and store it into specified address in memory
        void stor();

        // Pop top 2 trytes from stack and push their sum
        void add();

        // Pop top tryte from stack and push it's negation 
        void neg();

        // Pop top 2 trytes from stack and push their difference
        void sub();      

        // Pop top 2 trytes from stack and push their product
        void sub();        
    }
} // namespace termite

#endif