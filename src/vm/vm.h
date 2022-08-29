// -*- vm/vm.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef VM_H
#define VM_H

#include <cstdint>

#include "../core/trybble.h"
#include "../core/tryte.h"
#include "../core/word.h"
#include "memory.h"

namespace termite {
    class VM {
    public:
        Memory mem;

        std::array<Word, 27> regfile;

        // Methods for executing different instructions
        
        // No operation
        void nop() const;

        // System call
        void syscall(const Trybble &reg);

        // Add
        void add(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3); 

        // Subtract
        void sub(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3); 

        // Add immediate
        void addi(const Trybble &reg1, const Trybble &reg2, const Halfword &imm); 

        // Add unsigned
        void addu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3); 

        // Subtract unsigned
        void subu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3); 

        // Add immediate unsigned
        void addiu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Multiply
        void mul(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3); 

        // Multiply unsigned
        void mulu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3);

        // Divide
        void div(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3);

        // Divide unsigned
        void divu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3);

        // Tritwise AND
        void and_(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3);

        // Tritwise OR
        void or_(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3);

        // Tritwise AND immediate
        void andi(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Tritwise OR immediate
        void ori(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Load upper immediate
        void lui(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Load word
        void lw(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Store word
        void sw(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);
  
        // Branch unconditionally
        void b(const Addr &addr);

        // Branch if equal
        void beq(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if not equal
        void bne(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if less than
        void blt(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if less than unsigned
        void bltu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if greater than
        void bgt(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if greater than unsigned
        void bgtu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if less than or equal
        void ble(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if less than or equal unsigned
        void bleu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if greater than or equal
        void bge(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);

        // Branch if greater than unsigned
        void bgeu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm);
    };
}

#endif // VM_H