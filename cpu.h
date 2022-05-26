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

        void executeProgram(const std::vector<Word> &program);

        void executeInstr(const Instr &instr);       
    };
}

#endif