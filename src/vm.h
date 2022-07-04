#ifndef VM_H
#define VM_H

#include <string>
#include <vector>
#include <stack>

#include "tryte.h"
#include "word.h"

namespace termite
{
    class VM
    {
    protected:
        std::stack<Tryte> stack;

        Tryte pop_val();
    public:        
        VM() = default;

        void exec_program(const std::vector<Word> &program);
        void push(const Tryte &val);
        void pop();
        void swap();
        void in(const Tryte &mode);
        void out(const Tryte &mode);
        void add();
        void neg();
        void sub();
        void mul();
        void and_();
        void or_();
        void xor_();
    };
    
} // namespace termite

#endif