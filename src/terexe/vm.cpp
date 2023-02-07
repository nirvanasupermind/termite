#include <iostream>
#include <array>
#include <tuple>
#include "../core/tables.h"
#include "../core/trit.h"
#include "../core/tryte.h"
#include "../core/word.h"
#include "mem.h"
#include "opcode.h"
#include "vm.h"

namespace termite {
    VM::VM() {
        reset();
    }

    void VM::set_sign_flag(const Word& word) {
        if (word.to_int() == 0) {
            psw.set_trit(10, 0);
        }
        else if (!word.is_neg()) {
            psw.set_trit(10, 1);
        }
        else {
            psw.set_trit(10, 2);
        }
    }

    void VM::reset() {
        running = true;
        reg[VM::PC] = Word::from_int(1458);
        reg[VM::SP] = Word::from_int(728);
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
        // if(static_cast<int>(opcode) != 0) {
        // std::cout << "APOPLAALOALALOLOAAP JOURNALISM : " << static_cast<int>(opcode) << '\n';
        // }
        switch (opcode) {
        case Opcode::NOP: {
            fetch_tryte();
            break;
        }

        case Opcode::LDT: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int raddr = (tryte.to_int() % 81) / 9;
            reg[rdest] = Word::from_trytes(Tryte(), mem.data.at(reg.at(raddr).to_int()));
            break;
        }

        case Opcode::LDW: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int raddr = (tryte.to_int() % 81) / 9;
            reg[rdest] = mem.read_word(reg.at(raddr).to_int());
            break;
        }

        case Opcode::LDI: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int imm = tryte.to_int() % 81;
            reg[rdest] = Word::from_int(imm);
            break;
        }

        case Opcode::LDPS: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            reg[rdest] = psw;
            break;
        }

        case Opcode::STT: {
            Tryte tryte = fetch_tryte();
            int rsrc = tryte.to_int() / 81;
            int raddr = (tryte.to_int() % 81) / 9;
            mem.data[reg.at(raddr).to_int()] = reg.at(rsrc).lo_tryte();
            break;
        }

        case Opcode::STW: {
            Tryte tryte = fetch_tryte();
            int rsrc = tryte.to_int() / 81;
            int raddr = (tryte.to_int() % 81) / 9;
            mem.write_word(reg.at(raddr).to_int(), reg.at(rsrc));
            break;
        }

        case Opcode::NEG: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            reg[rdest] = -reg[rdest];
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::ADD: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word sum;
            Trit carry;
            std::tie(sum, carry) = reg[rdest] + reg[rsrc];
            reg[rdest] = sum;
            psw.set_trit(11, carry);
            set_sign_flag(sum);
            break;
        }

        case Opcode::ADDI: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int imm = tryte.to_int() % 81;
            Word sum;
            Trit carry;
            std::tie(sum, carry) = reg[rdest] + Word::from_int(imm);
            reg[rdest] = sum;
            psw.set_trit(11, carry);
            set_sign_flag(sum);
            break;
        }

        case Opcode::ADDC: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word sum;
            Trit carry;
            std::tie(sum, carry) = reg[rdest] + ((reg[rsrc] + Word::from_int(psw.get_trit(11).to_int())).first);
            reg[rdest] = sum;
            psw.set_trit(11, carry);
            set_sign_flag(sum);
            break;
        }

        case Opcode::SUB: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word sum;
            Trit borrow;
            std::tie(sum, borrow) = reg[rdest] + reg[rsrc];
            reg[rdest] = sum;
            psw.set_trit(11, borrow);
            set_sign_flag(sum);
            break;
        }

        case Opcode::SUBB: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word diff;
            Trit borrow;
            std::tie(diff, borrow) = reg[rdest] - ((reg[rsrc] + Word::from_int(psw.get_trit(11).to_int())).first);
            reg[rdest] = diff;
            psw.set_trit(11, borrow);
            set_sign_flag(diff);
            break;
        }

        case Opcode::MUL: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            reg[rdest] = reg.at(rdest) * reg.at(rsrc);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::UDIV: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word quot;
            Word rem;
            std::tie(quot, rem) = reg[rdest].udiv(reg[rsrc]);
            reg[rdest] = quot;
            reg[rdest + 1] = rem;
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::SDIV: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word quot;
            Word rem;
            std::tie(quot, rem) = reg[rdest].sdiv(reg[rsrc]);
            reg[rdest] = quot;
            reg[rdest + 1] = rem;
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::SL: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int imm = tryte.to_int() % 81;
            reg[rdest] = reg.at(rdest) >> imm;
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::ASR: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int imm = tryte.to_int() % 81;
            reg[rdest] = reg.at(rdest).asr(imm);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::LSR: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int imm = tryte.to_int() % 81;
            reg[rdest] = reg.at(rdest).lsr(imm);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::NOT: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            reg[rdest] = ~reg[rdest];
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::AND: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            reg[rdest] = reg.at(rdest) & reg.at(rsrc);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::OR: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            reg[rdest] = reg.at(rdest) | reg.at(rsrc);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::XOR: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            reg[rdest] = reg.at(rdest) ^ reg.at(rsrc);
            set_sign_flag(reg.at(rdest));
            break;
        }

        case Opcode::CMP: {
            Tryte tryte = fetch_tryte();
            int rdest = tryte.to_int() / 81;
            int rsrc = (tryte.to_int() % 81) / 9;
            Word sum;
            Trit borrow;
            std::tie(sum, borrow) = reg[rdest] + reg[rsrc];
            psw.set_trit(11, borrow);
            set_sign_flag(sum);
            break;
        }

        case Opcode::JMP: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            reg[VM::PC] = reg[raddr];
            break;
        }

        case Opcode::JE: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() == 0) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::JNE: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() != 0) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::JL: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() == 2) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::JLE: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() != 1) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::JG: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() == 1) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::JGE: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            if (psw.get_trit(11).to_int() != 2) {
                reg[VM::PC] = reg[raddr];
            }
            break;
        }

        case Opcode::PUSH: {
            Tryte tryte = fetch_tryte();
            int rsrc = tryte.to_int() / 81;
            Word sp = reg.at(VM::SP);
            mem.write_word(sp.to_int(), reg.at(rsrc));
            reg[VM::SP] = (sp - Word::from_int(2)).first;
            break;
        }

        case Opcode::POP: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            Word sp = reg.at(VM::SP);
            mem.write_word(reg.at(raddr).to_int(), mem.read_word(sp.to_int()));
            reg[VM::SP] = (sp + Word::from_int(2)).first;
            break;
        }

        case Opcode::CALL: {
            Tryte tryte = fetch_tryte();
            int raddr = tryte.to_int() / 81;
            Word sp = reg.at(VM::SP);
            mem.write_word(sp.to_int(), reg.at(VM::PC));
            reg[VM::SP] = (sp - Word::from_int(2)).first;
            reg[VM::PC] = reg[raddr];
            break;
        }

        case Opcode::RET: {
            fetch_tryte();
            Word sp = reg.at(VM::SP);
            mem.write_word(reg.at(VM::PC).to_int(), mem.read_word(sp.to_int()));
            reg[VM::SP] = (sp + Word::from_int(2)).first;
            break;
        }

        case Opcode::SYSCALL: {
            Tryte service = fetch_tryte();
            if (service.to_int() == 0) {
                running = false;
            }
            else if (service.to_int() == 1) {
                wchar_t ch;
                std::wcin >> ch;
                reg[0] = Word::from_int(TCS_CHAR_TO_CODEPOINT.at(ch));
            }
            else if (service.to_int() == 2) {
                std::wcout << CODEPOINT_TO_TCS_CHAR.at(reg.at(0).to_int());
            }
            else if (service.to_int() == 3) {
                int val;
                std::cin >> val;
                reg[0] = Word::from_int(val);
            }
            else if (service.to_int() == 4) {
                std::cout << reg.at(0).to_int();
            }
            else if (service.to_int() == 5) {
                std::cout << reg.at(0).to_ter_string();
            }
            else if (service.to_int() == 6) {
                std::cout << reg.at(0).to_non_string();
            }
            break;
        }
        }
    }

    void VM::run() {
        while (running) {
            step();
        }
    }
} // namespace termite