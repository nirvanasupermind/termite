#include <iostream>
#include <array>
#include "tryte.h"
#include "word.h"
#include "mem.h"
#include "opcode.h"

#include "vm.h"

namespace termite
{
    VM::VM() {
        reset();
    }

    void VM::reset() {
        reg[VM::PC] = Word::from_int(531440);
    }

    Tryte VM::fetch_tryte() {
        reg[VM::PC] = (reg[VM::PC] + Word::ONE).first;

        return mem.data.at(reg[VM::PC].to_int());
    }

    Word VM::fetch_word() {
        reg[VM::PC] = (reg[VM::PC] + Word::from_int(2)).first;

        return mem.read_word(reg[VM::PC].to_int());
    }

    void VM::step() {
        Opcode opcode = static_cast<Opcode>(fetch_tryte().to_int());
        switch(opcode) {
            case Opcode::INT: {
                Tryte interrupt_code = fetch_tryte();
                
                if(interrupt_code.to_int() == 0) {
                    std::exit(0);   
                } else if (interrupt_code.to_int() == 3) {
                    std::cout << reg.at(0).to_int() << '\n';
                }
            }
        }
    }

    void VM::run() {
        while(true) {
            step();
        }
    }
} // namespace termite