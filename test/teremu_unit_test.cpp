
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/teremu/cpu.h"

int main(int argc, char** argv) {
    termite::Mem memory;
    termite::CPU cpu;
    std::cout << "*** TEREMU UNIT TEST" << '\n';
    std::vector<std::vector<std::string> > tests{
        // push_imm_pop_to_reg
        {"DCD0 0000 0000 001A 0000 0000 DBC3 0000 0000 0000 0000 0000", "8", "push_imm_pop_to_reg"},
        // and_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D1C3 C200 0000 0000 0000 0000", "5", "and_regs"},
        // or_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D2C3 C200 0000 0000 0000 0000", "10", "or_regs"},
        // xor_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D3C3 C200 0000 0000 0000 0000", "-8", "xor_regs"},
        // shl_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D4C3 C200 0000 0000 0000 0000", "17496", "shl_regs"},
        // shr_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 0001 CDC3 C200 0000 0000 0000 0000", "3", "shr_regs"},
        // add_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CCC3 C200 0000 0000 0000 0000", "15", "add_regs"},
        // adc_regs
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CBC3 C200 0000 0000 0000 0000", "16", "adc_regs"},
        // sub_regs3
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CAC3 C200 0000 0000 0000 0000", "1", "sub_regs"},
        // sbb_regs
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B C0C3 C200 0000 0000 0000 0000", "0", "sbb_regs"},
        // mul_regs_lo
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C1C2 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "21523359", "mul_regs_lo"},
        // mul_regs_hi
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C1C2 0000 0000 0000 0000 0000", "2", "mul_regs_hi"},
        // div_regs_quo
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C2C2 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "7174453", "div_regs_quo"},
        // div_regs_rem
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C2C2 0000 0000 0000 0000 0000", "1", "div_regs_rem"},
        // neg_reg
        {"DDC3 D000 0000 0000 0000 001A C3C3 0000 0000 0000 0000 0000", "-8", "neg_reg"},
        // cmp_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B C4C3 C200 0000 0000 0000 0000 DA00 0000 0000 0000 0000 0000 DBC3 0000 0000 0000 0000 0000", "3", "cmp_regs"},
        // and_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC D1C3 D000 0000 0000 0000 001D", "-40", "and_reg_imm"},
        // or_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC D2C3 D000 0000 0000 0000 001D", "6", "or_reg_imm"},
        // xor_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC D3C3 D000 0000 0000 0000 001D", "6", "xor_reg_imm"},
        // shl_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC D4C3 D000 0000 0000 0000 001D", "-9477", "shl_reg_imm"},
        // shr_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC CDC3 D000 0000 0000 0000 001D", "0", "shr_reg_imm"},
        // add_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC CCC3 D000 0000 0000 0000 001D", "-34", "add_reg_imm"},
        // adc_reg_imm
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 00DC CBC3 D000 0000 0000 0000 001D", "-33", "adc_reg_imm"},
        // sub_reg_imm
        {"DDC3 D000 0000 0000 0000 00DC CAC3 D000 0000 0000 0000 001D", "-44", "sub_reg_imm"},
        // sbb_reg_imm
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 00DC C0C3 D000 0000 0000 0000 001D", "-45", "sbb_reg_imm"},
        // mul_reg_imm_lo
        {"DDCD D000 0000 0000 4444 4444 C1D0 0000 0000 001D 0000 0000 DDC3 CD00 0000 0000 0000 0000", "21523358", "mul_reg_imm_lo"},
        // mul_reg_imm_hi
        {"DDCD D000 0000 0000 4444 4444 C1D0 0000 0000 001D 0000 0000", "2", "mul_reg_imm_hi"},
        // and_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 D1B0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "-1004", "and_disp_imm"},
        // or_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 D2B0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "256", "or_disp_imm"},
        // xor_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 D3B0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "248", "xor_disp_imm"},
        // shl_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 D4B0 D000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "714", "shl_disp_imm"},
        // shr_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 CDB0 D000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "79", "shr_disp_imm"},
        // add_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 CCB0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "-748", "add_disp_imm"},      
        // adc_disp_imm
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDB0 D000 0000 0000 0000 03A4 CBB0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "-747", "adc_disp_imm"},      
        // sub_disp_imm
        {"DDB0 D000 0000 0000 0000 03A4 CAB0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "1224", "sub_disp_imm"},
        // sbb_disp_imm
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDB0 D000 0000 0000 0000 03A4 C0B0 D000 0000 0000 0000 ACB4 DDC3 B000 0000 0000 0000 0000", "1223", "sbb_disp_imm"},
        // mul_reg_disp_lo
        {"DDCD D000 0000 0000 4444 4444 DDB0 D000 0000 0000 0000 0003 C1B0 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "21523359", "mul_reg_disp_lo"},
        // mul_reg_disp_hi
        {"DDCD D000 0000 0000 4444 4444 DDB0 D000 0000 0000 0000 0003 C1B0 0000 0000 0000 0000 0000", "2", "mul_reg_disp_hi"},
        // div_reg_disp_quo
        {"DDCD D000 0000 0000 4444 4443 DDB0 D000 0000 0000 0000 001C C2B0 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "3587226", "div_reg_disp_quo"},
        // div_reg_disp_rem
        {"DDCD D000 0000 0000 4444 4443 DDB0 D000 0000 0000 0000 001C C2B0 0000 0000 0000 0000 0000", "3", "div_reg_disp_rem"},        
        // and_disps
        {"DDB0 D000 0000 0000 0000 033A DDB0 D000 0000 0001 0000 10DD D1B0 B000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "-40", "and_disps"},
        // or_disps
        {"DDB0 D000 0000 0000 0000 033A DDB0 D000 0000 0001 0000 10DD D2B0 B000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "998", "or_disps"},
        // xor_disps
        {"DDB0 D000 0000 0000 0000 033A DDB0 D000 0000 0001 0000 10DD D3B0 B000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "26", "xor_disps"},
        // xor_disps
        {"DDB0 D000 0000 0000 0000 033A DDB0 D000 0000 0001 0000 10DD D3B0 B000 0000 0000 0000 0001 DDC3 B000 0000 0000 0000 0000", "26", "xor_disps"},        
        // jmp_to_exit
        {"BBD0 0000 DDDD DDCA 0000 0000 DDC3 D000 0000 0000 0000 0004", "0", "jmp_to_exit"},
        // jl_to_exit_true
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 BAD0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jl_to_exit_true"},
        // jl_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0001 BAD0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "jl_to_exit_false"},
        // jle_to_exit_true1
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0002 B0D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jle_to_exit_true1"},
        // jle_to_exit_true2
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 B0D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jle_to_exit_true2"},
        // jle_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0001 B0D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "jle_to_exit_false"},
        // jg_to_exit_true
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0001 B1D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jg_to_exit_true"},
        // jg_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 B1D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "jg_to_exit_false"},
        // jge_to_exit_true1
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0002 B2D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jge_to_exit_true1"},
        // jge_to_exit_true2
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0001 B2D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jge_to_exit_true2"},
        // jge_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 B2D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "jge_to_exit_false"},
        // je_to_exit_true
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0002 B2D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "je_to_exit_true"},   
        // je_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 B2D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "je_to_exit_false"},
        // jne_to_exit_true
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0003 B3D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "2", "jne_to_exit_true"},   
        // jne_to_exit_false
        {"DDC3 D000 0000 0000 0000 0002 C4C3 D000 0000 0000 0000 0002 B4D0 0000 DDDD DDB2 0000 0000 DDC3 D000 0000 0000 0000 0004", "4", "jne_to_exit_false"}
    };

    int num_passed = 0;
    for (int i = 0; i < tests.size(); i++) {
        try {
            cpu.exec_text(tests[i][0], memory);
            if (cpu.regs[7].to_int32() == std::stoi(tests[i][1])) {
                std::cout << "test " + tests[i][2] + " passed";
                num_passed++;
            }
            else {
                std::cout << "test " + tests[i][2] + " failed";
            }
            std::cout << " with DX = " << cpu.regs[7].to_int32() << '\n';
        }
        catch (const std::string& e) {
            std::cerr << "error: " << e << '\n';
            return 1;
        }
    }
    if (num_passed == tests.size()) {
        std::cout << "*** ALL TESTS PASSED" << '\n';
    }
    else {
        std::cout << "*** " << num_passed << '/' << tests.size() << " TESTS PASSED" << '\n';
    }
    return 0;
}