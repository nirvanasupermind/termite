#include "word.h"
#include "cpu.h"

namespace termite {
    void Mem::initialize() {
        for(uint32_t i = 0; i < MAX_MEM; i++) {
            data[i] = 0;
        }
    }

    Tryte Mem::get_tryte(uint32_t addr) const {
        return data[addr];
    }

    Tryte Mem::get_tryte(const Word& addr) const {
        return data[addr.to_int32() + 21523360];
    }

    Word Mem::get_word(const Word& addr) const {
        return Word(get_tryte(addr), get_tryte(addr + Word::ONE));
    }

    void Mem::set_word(const Word& addr, const Word& val) {
        data[addr.to_int32() + 21523360] = val.get_lo_tryte();
        data[addr.to_int32() + 21523361] = val.get_hi_tryte();
    }

    void CPU::reset(Mem& memory) {
        for(int i = 0; i < 7; i++) {
            regs[i] = 0;
        }
        regs[7] = Word::from_int32(21523360);
        regs[8] = Word::from_int32(-21523360); 
        memory.initialize();
    }

    Tryte CPU::fetch_tryte(Word& cycles, Mem& memory) {
        Tryte data = memory[regs[8]];
        regs[8] = regs[8] + Word::ONE;
        cycles = cycles - Word::ONE;
    } 

    Word CPU::fetch_word(Word& cycles, Mem& memory) {
        return Word(fetch_tryte(cycles, memory), fetch_tryte(cycles, memory));
    } 

    Word CPU::get_addr_mode(Word& cycles, Mem& memory, uint8_t mode, const Word& reg) {
          if(mode == 0) {
            return fetch_word(cycles, memory);
         } else if(mode == 1) {
            return regs[reg.to_int32() + 4];
         } else {
            return memory.get_word(regs[reg.to_int32() + 4] + fetch_word(cycles, memory));
         }
    }

    void CPU::execute(Word& cycles, Mem& memory) {
        while(cycles > Word::ZERO) {
            Word ins = fetch_word(cycles, memory);
            Word opcode = ins.get_trit_range(12, 15);
            switch(opcode.to_int32()) {
                case INS_MOV: {
                    uint8_t dest_mode = ins.get_bct_trit(11);
                    Word dest_reg = ins.get_trit_range(9, 10);

                    uint8_t src_mode = ins.get_bct_trit(8);
                    Word src_reg = ins.get_trit_range(6, 7);
                    if(dest_mode == 1) {
                        regs[dest_reg.to_int32() + 4] = get_addr_mode(cycles, memory, src_mode, src_reg);
                    } else {
                        Word addr = regs[dest_reg.to_int32() + 4] + fetch_word(cycles, memory);
                        memory.set_word(addr, get_addr_mode(cycles, memory, src_mode, src_reg));
                    }
                    break;
                }

            }
        }
    } 
}