#ifndef VM_H
#define VM_H

#include <string>
#include <vector>
#include <unordered_map>

#include "../core/duet.h"
#include "../core/tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    class VM
    {
    protected:
        std::unordered_map<Word, Tryte, Word::HashFunction> mem;
        Tryte accum_reg;
        Tryte x_reg;
        Tryte y_reg;
    public:        
        VM() = default;

        void exec_program(const std::vector<Instr> &program);
        void lda(const Word &operand, const Duet &addr_mode);
        void sta(const Word &operand, const Duet &addr_mode);
        void ldx(const Word &operand, const Duet &addr_mode);
        void stx(const Word &operand, const Duet &addr_mode);
        void ldy(const Word &operand, const Duet &addr_mode);
        void sty(const Word &operand, const Duet &addr_mode);
    };
    
} // namespace termite

#endif