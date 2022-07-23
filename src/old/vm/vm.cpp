#include <iostream>
#include <string>
#include <array>

#include "../core/duet.h"
#include "../core/tryte.h"
#include "../core/exceptions.h"
#include "word.h"
#include "instr.h"
#include "decoder.h"
#include "vm.h"

namespace termite
{
    Tryte VM::interpret_addr_mode(const Word &addr, const Duet &addr_mode, const std::string &instr) const
    {
        switch (addr_mode.to_int())
        {
        case 0:
            return mem.load(addr);
        case 1:
            return addr.hi;
        default:
            throw TermiteException(std::string("invalid addressing mode for instruction \"" + instr + "\": ") + addr_mode.to_chr());
        }
    }

    void VM::exec_program()
    {
        while (true)
        {
            Tryte t1 = mem.load(pc_reg);
            pc_reg.inc();
            Tryte t2 = mem.load(pc_reg);
            pc_reg.inc();
            Tryte t3 = mem.load(pc_reg);
            pc_reg.inc();

            Instr instr = decode_instr(t1, t2, t3);
            exec_instr(instr);
        }
    }

    void VM::exec_instr(const Instr &instr)
    {
        std::cout << (int)instr.op << '\n';

        switch(instr.op) 
        {
        case Op::NOP:
            break;
        case Op::RET:
            ret(instr.addr, instr.addr_mode);
            break;
        case Op::LDA:
            lda(instr.addr, instr.addr_mode);
            break;
        default:
            throw TermiteException(std::string("unimplemented"));
        }
    }

    void VM::ret(const Word &addr, const Duet &addr_mode)
    {
        Tryte tryte = interpret_addr_mode(addr, addr_mode, "ret");

        int i = tryte.to_int();

        if(i == 0)
        {
            std::exit(0);
        } else
        {
            std::exit(1);
        }
    }

    void VM::lda(const Word &addr, const Duet &addr_mode)
    {
        Tryte tryte = interpret_addr_mode(addr, addr_mode, "lda");

        accum_reg = tryte;
    }

    void VM::sta(const Word &addr, const Duet &addr_mode)
    {
        if (addr_mode.to_int() == 0)
        {
            mem.store(addr, accum_reg);
        }
        
        throw TermiteException(std::string("invalid addressing mode for instruction \"sta\": ") + addr_mode.to_chr());
    }

    void VM::ldx(const Word &addr, const Duet &addr_mode)
    {
        switch (addr_mode.to_int())
        {
        case 0:
            x_reg = mem.load(addr);
            break;
        case 1:
            x_reg = addr.lo;
            break;
        default:
            throw TermiteException(std::string("invalid addressing mode for instruction \"ldx\": ") + addr_mode.to_chr());
            break;
        }
    }

    void VM::stx(const Word &addr, const Duet &addr_mode)
    {
        switch (addr_mode.to_int())
        {
        case 0:
            mem.store(addr, x_reg);
            break;
        default:
            throw TermiteException(std::string("invalid addressing mode for instruction \"stx\": ") + addr_mode.to_chr());
            break;
        }
    }

    void VM::ldy(const Word &addr, const Duet &addr_mode)
    {
        switch (addr_mode.to_int())
        {
        case 0:
            mem.store(addr, x_reg);
            break;
        default:
            throw TermiteException(std::string("invalid addressing mode for instruction \"stx\": ") + addr_mode.to_chr());
            break;
        }
    }
} // namespace termite