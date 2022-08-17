// -*- vm/opcode.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef OPCODE_H
#define OPCODE_H

#include <cstdint>

#include "../core/tryte.h"


namespace termite {
    // Specifies the operation to be performed in a CPU instruction.
    class Opcode {
    public:
        uint8_t val;

        Opcode(uint8_t val);

        Opcode(const Tryte& tryte);

        static const Opcode NOP;
        static const Opcode INT;
        static const Opcode SYS;
        static const Opcode LD;
        static const Opcode LDI;
        static const Opcode ST;
        static const Opcode STI;
        static const Opcode NEG;
        static const Opcode ADD;
        static const Opcode ADDU;
        static const Opcode SUB;
        static const Opcode SUBU;
        static const Opcode MUL;
        static const Opcode MULU;
        static const Opcode ADD;
        static const Opcode ADDU;
    };
}

#endif // OPCODE_H