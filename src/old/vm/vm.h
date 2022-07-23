#ifndef VM_H
#define VM_H

#include <string>
#include <array>

#include "../core/duet.h"
#include "../core/tryte.h"
#include "word.h"
#include "instr.h"
#include "memory.h"

namespace termite
{
    class VM
    {
    protected:
        Tryte interpret_addr_mode(const Word &addr, const Duet &addr_mode, const std::string &instr) const;
    public:  
        Memory mem;
        Tryte accum_reg;
        Tryte x_reg;
        Tryte y_reg;
        Word pc_reg;

        VM() = default;

        // Reads instructions from memory to execute a program
        void exec_program();

        void exec_instr(const Instr &instr);
        void ret(const Word &addr, const Duet &addr_mode);
        void lda(const Word &addr, const Duet &addr_mode);
        void sta(const Word &addr, const Duet &addr_mode);
        void ldx(const Word &addr, const Duet &addr_mode);
        void stx(const Word &addr, const Duet &addr_mode);
        void ldy(const Word &addr, const Duet &addr_mode);
        void sty(const Word &addr, const Duet &addr_mode);
    };
    
} // namespace termite

#endif