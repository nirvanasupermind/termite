#ifndef VM_H
#define VM_H

#include <string>
#include <vector>
#include <unordered_map>

#include "tryte.h"
#include "word.h"

namespace termite
{
    class VM
    {
    protected:
        std::unordered_map<Tryte, Tryte, Tryte::HashFunction> mem;
        Tryte accum;

    public:        
        VM() = default;

        void exec_program(const std::vector<Word> &program);

        void mov(const Tryte &op1, const Tryte &op2);

        void sto(const Tryte &op1, const Tryte &op2);

        void lda(const Tryte &op1);

        void sta(const Tryte &op1);

        void in(const Tryte &op1);

        void out(const Tryte &op1);

        void add(const Tryte &op1, const Tryte &op2);

        void neg(const Tryte &op1);

        void sub(const Tryte &op1, const Tryte &op2);

        void mul(const Tryte &op1, const Tryte &op2);

        void shl(const Tryte &op1, const Tryte &op2);

        void shr(const Tryte &op1, const Tryte &op2);

        void cmp(const Tryte &op1, const Tryte &op2);   
    };
    
} // namespace termite

#endif