#ifndef CPU_H
#define CPU_H

#include <string>
#include <vector>
#include <stack>

#include "tryte.h"
#include "word.h"
#include "instr.h"
#include "text.h"

namespace termite
{
    class CPU 
    {
    public:
        std::stack<Tryte> stack;

        CPU() = default;

        // Push to stack
        void push(const Tryte &val);

        // Pop top stack item
        void pop();

        // Swap top 2 stack items

        void swap();

        // Syscall (all-in-one for most I/O operations)

        void syscall(const Tryte &val);

        // Pop top 2 stack items, then push their addition

        void add();

        // Pop top 2 stack items, then push their subtraction

        void sub();

        // Pop top 2 stack items, then push their multiplication

        void mul();

        // Pop top stack item, then push it's negation

        void neg();

        // Pop top 2 stack items, then push their "trit-wise" AND

        void and_();

        // Pop top 2 stack items, then push their "trit-wise" OR

        void or_();

        // Pop top 2 stack items, and push their "trit-wise" XOR

        void xor_();

        // Pop top 2 stack items, and push their "trit-wise" NOT

        void not_();
    };
}

#endif