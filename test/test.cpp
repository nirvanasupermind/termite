#include <cassert>
#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>

#include "../src/util.hpp"
#include "../src/tables.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"
#include "../src/word.hpp"
#include "../src/opcodes.hpp"
#include "../src/vm.hpp"

const bool verbose = false;

void test_tables() {
    int native_int = 5;
    uint8_t bct_trybble_a = 0b01'10'10; // decimal 17, sept H, ternary 212
    uint8_t bct_trybble_b = 0b00'01'00; // decimal 3, sept 3, ternary 010

    assert(termite::NATIVE_INT_TO_BCT_TRYBBLE.at(native_int) == 0b00'01'10);

    assert(termite::BCT_TRYBBLE_TO_NATIVE_INT.at(bct_trybble_a) == 17);
    assert(termite::BCT_TRYBBLE_TO_SEPT_STR.at(bct_trybble_a) == "H");

    assert(termite::BCT_TRYBBLE_TO_NATIVE_INT.at(bct_trybble_b) == 3);
    assert(termite::BCT_TRYBBLE_TO_SEPT_STR.at(bct_trybble_b) == "3");

    assert(termite::BCT_TRYBBLE_AND.at(bct_trybble_a).at(bct_trybble_b) == 0b00'01'00);
    assert(termite::BCT_TRYBBLE_OR.at(bct_trybble_a).at(bct_trybble_b) == 0b01'10'10);
    assert(termite::BCT_TRYBBLE_XOR.at(bct_trybble_a).at(bct_trybble_b) == 0b01'00'10);

    std::cout << "test_tables: All tests succeeded" << '\n';
}


void test_trybble() {
    termite::Trybble trybble_a(0b01'01'10); // decimal 14, sept E, ternary 112
    termite::Trybble trybble_b(termite::native_int, 20); // decimal 20, sept K, ternary 202
    termite::Trybble trybble_c(termite::sept, "A"); // decimal 10, sept A, ternary 101

    // 112
    // 202

    assert(static_cast<int>(trybble_a & trybble_b) == 11);
    assert(static_cast<int>(trybble_a | trybble_b) == 23);
    assert(static_cast<int>(trybble_a ^ trybble_b) == 4);

    assert(static_cast<int>(trybble_a & trybble_c) == 10);
    assert(static_cast<int>(trybble_a | trybble_c) == 14);
    assert(static_cast<int>(trybble_a ^ trybble_c) == 21);

    assert(static_cast<int>(trybble_b & trybble_c) == 10);
    assert(static_cast<int>(trybble_b | trybble_c) == 20);
    assert(static_cast<int>(trybble_b ^ trybble_c) == 0);

    assert(static_cast<int>(~trybble_a) == 12);
    assert(trybble_a.get_bct() == 0b01'01'10);
    assert(static_cast<int>(trybble_a) == 14);
    assert(static_cast<std::string>(trybble_a) == "E");

    assert(static_cast<int>(~trybble_b) == 6);
    assert(trybble_b.get_bct() == 0b10'00'10);
    assert(static_cast<int>(trybble_b) == 20);
    assert(static_cast<std::string>(trybble_b) == "K");

    assert(static_cast<int>(~trybble_c) == 16);
    assert(trybble_c.get_bct() == 0b01'00'01);
    assert(static_cast<int>(trybble_c) == 10);
    assert(static_cast<std::string>(trybble_c) == "A");

    std::cout << "test_trybble: All tests succeeded" << '\n';
}

void test_tryte() {
    termite::Tryte tryte_a(termite::Trybble(termite::sept, "4"), termite::Trybble(termite::sept, "D")); // decimal 121, sept 4D, ternary 011111
    termite::Tryte tryte_b(termite::native_int, 188); // decimal 188, sept 6Q, ternary 020222
    termite::Tryte tryte_c(termite::sept, "01"); // decimal 1, sept 01, ternary 000001

    // 011111
    // 020222
    // 010111


    assert(static_cast<int>(tryte_a & tryte_b) == 94);
    assert(static_cast<int>(tryte_a | tryte_b) == 215);
    assert(static_cast<int>(tryte_a ^ tryte_b) == 27);

    assert(static_cast<int>(tryte_a & tryte_c) == 1);
    assert(static_cast<int>(tryte_a | tryte_c) == 121);
    assert(static_cast<int>(tryte_a ^ tryte_c) == 122);

    assert(static_cast<int>(tryte_b & tryte_c) == 1);
    assert(static_cast<int>(tryte_b | tryte_c) == 188);
    assert(static_cast<int>(tryte_b ^ tryte_c) == 186);

    assert(static_cast<int>(~tryte_a) == 607);
    assert(static_cast<int>(tryte_a.get_hi()) == 4);
    assert(static_cast<int>(tryte_a.get_lo()) == 13);
    assert(static_cast<int>(tryte_a) == 121);
    assert(static_cast<std::string>(tryte_a) == "4D");

    assert(static_cast<int>(~tryte_b) == 540);
    assert(static_cast<int>(tryte_b.get_hi()) == 6);
    assert(static_cast<int>(tryte_b.get_lo()) == 26);
    assert(static_cast<int>(tryte_b) == 188);
    assert(static_cast<std::string>(tryte_b) == "6Q");

    assert(static_cast<std::string>(~tryte_c) == "QP");
    assert(static_cast<int>(tryte_c.get_hi()) == 0);
    assert(static_cast<int>(tryte_c.get_lo()) == 1);
    assert(static_cast<int>(tryte_c) == 1);
    assert(static_cast<std::string>(tryte_c) == "01");

    std::cout << "test_tryte: All tests succeeded" << '\n';
}

void test_word() {
    termite::Word word_a(termite::Tryte(termite::sept, "0C"), termite::Tryte(termite::sept, "CJ")); // decimal 9091, sept 0CCJ, ternary 0000110110201
    termite::Word word_b(termite::native_int, 14152); // decimal 14152, sept 0JB4, ternary 0000201102011
    termite::Word word_c(termite::native_int, 4170); // decimal 4170, sept 05JC, ternary 0000012201110

    // 0000110110201
    // 0000201102011
    // 0000011212212

    assert(static_cast<int>(word_a + word_b) == 23243);
    assert(static_cast<int>(word_a - word_b) == 526380);
    assert(static_cast<int>(word_a * word_b) == 47110);
    assert(static_cast<int>(word_a / word_b) == 0);
    assert(static_cast<int>(word_a % word_b) == 9091);
    assert(static_cast<int>(word_a & word_b) == 6805);
    assert(static_cast<int>(word_a | word_b) == 16438);
    assert(static_cast<int>(word_a ^ word_b) == 3560);

    assert(static_cast<int>(word_a + word_c) == 13261);
    assert(static_cast<int>(word_a - word_c) == 4921);
    assert(static_cast<int>(word_a * word_c) == 177159);
    assert(static_cast<int>(word_a / word_c) == 2);
    assert(static_cast<int>(word_a % word_c) == 751);
    assert(static_cast<int>(word_a & word_c) == 2439);
    assert(static_cast<int>(word_a | word_c) == 10822);
    assert(static_cast<int>(word_a ^ word_c) == 12505);

    assert(static_cast<int>(word_b + word_c) == 18322);
    assert(static_cast<int>(word_b - word_c) == 9982);    
    assert(static_cast<int>(word_b * word_c) == 23889);  
    assert(static_cast<int>(word_b / word_c) == 3);  
    assert(static_cast<int>(word_b % word_c) == 1642); 
    assert(static_cast<int>(word_b & word_c) == 1002);     
    assert(static_cast<int>(word_b | word_c) == 17320);     
    assert(static_cast<int>(word_b ^ word_c) == 15325);

    assert(static_cast<int>(~word_a) == 522349);
    assert(static_cast<int>(word_a.get_hi()) == 12);
    assert(static_cast<int>(word_a.get_lo()) == 343);
    assert(static_cast<int>(word_a) == 9091);
    assert(static_cast<std::string>(word_a) == "0CCJ"); 

    assert(static_cast<int>(~word_b) == 517288);
    assert(static_cast<int>(word_b.get_hi()) == 19);
    assert(static_cast<int>(word_b.get_lo()) == 301);
    assert(static_cast<int>(word_b) == 14152);
    assert(static_cast<std::string>(word_b) == "0JB4"); 

    assert(static_cast<int>(~word_c) == 527270);
    assert(static_cast<int>(word_c.get_hi()) == 5);
    assert(static_cast<int>(word_c.get_lo()) == 525);
    assert(static_cast<int>(word_c) == 4170);
    assert(static_cast<std::string>(word_c) == "05JC"); 

    std::cout << "test_word: All tests succeeded" << '\n';
}

void test_mov(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "02", // mov [abs, imm]
        "10", "00", // 0s1000
        "09", "3M", // #6664
        "06", // mov [reg, abs]
        "00", // r0
        "10", "00", // 0s1000
        "01", // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 6664);   
    vm.clear();
    std::cout << "test_mov: All tests succeeded" << '\n';
}

void test_add(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "05", // mov [reg, imm]
        "00", // r0
        "0C", "1H", // #8792
        "05", // mov [reg, imm]
        "01", // r1
        "00", "G6", // #438
        "0D", // add [reg, reg]
        "01", // r0, r1
        "01" // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 9230);   
    vm.clear();
    std::cout << "test_add: All tests succeeded" << '\n';
}

void test_sub(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "05", // mov [reg, imm]
        "00", // r0
        "01", "7Q", // #944
        "02", // mov [abs, imm]
        "10", "00", // 0s1000
        "06", "QC", // #5088
        "0O", // sub [reg, abs]
        "00", // r0
        "10", "00", // 0s1000
        "01" // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 527297);   
    vm.clear();
    std::cout << "test_sub: All tests succeeded" << '\n';
}

void test_mul(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "05", // mov [reg, imm]
        "00", // r0
        "08", "H3", // #6294
        "12", // mul [reg, imm]
        "00", // r0
        "08", "KM", // #6394
        "01" // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 385761);   
    vm.clear();
    std::cout << "test_mul: All tests succeeded" << '\n';
}

void test_div(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "02", // mov [abs, imm]
        "10", "00", // 0s1000
        "0D", "B4", // #9778
        "15", // div [abs, imm]
        "10", "00", // 0s1000
        "00", "AC", // #282
        "06", // mov [reg, abs]
        "00", // r0
        "10", "00", // 0s1000        
        "01" // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 34);   
    vm.clear();
    std::cout << "test_div: All tests succeeded" << '\n';
}

void test_mod(termite::VM &vm) {
    vm.load_machine_code(std::vector<std::string>{
        "02", // mov [abs, imm]
        "10", "00", // 0s1000
        "0B", "J9", // #8541
        "02", // mov [abs, imm]
        "10", "02", // 0s1002
        "00", "1I", // #45
        "1C", // mod [abs, abs]
        "10", "00", // 0s1000
        "10", "02", // 0s1002
        "06", // mov [reg, abs]
        "00", // r0
        "10", "00", // 0s1000        
        "01" // hlt
    });

    vm.run(verbose);
    vm.assert_register_val(0, 36);   
    vm.clear();
    std::cout << "test_mod: All tests succeeded" << '\n';
}

int main() {
    termite::VM vm;

    test_tables();
    test_trybble();
    test_tryte();    
    test_word();
    test_mov(vm);
    test_add(vm);
    test_sub(vm);
    test_mul(vm);
    test_div(vm);
    test_mod(vm);
    
    return 0;
} 