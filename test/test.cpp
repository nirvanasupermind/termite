#include <iostream>
#include <cassert>
#include <string>

#include "../src/util.hpp"
#include "../src/tables.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"
#include "../src/word.hpp"
#include "../src/mem.hpp"
#include "../src/cpu.hpp"

void test_tables() {
    int native_int = 5;
    char bct_trybble_a = 0b01'10'10; // decimal 17, sept H, ternary 212
    char bct_trybble_b = 0b00'01'00; // decimal 3, sept 3, ternary 010

    assert(termite::NATIVE_INT_TO_BCT_TRYBBLE.at(native_int) == 0b00'01'10);

    assert(termite::BCT_TRYBBLE_TO_NATIVE_INT.at(bct_trybble_a) == 17);
    assert(termite::BCT_TRYBBLE_TO_SEPT_DIGIT.at(bct_trybble_a) == 'H');

    assert(termite::BCT_TRYBBLE_TO_NATIVE_INT.at(bct_trybble_b) == 3);
    assert(termite::BCT_TRYBBLE_TO_SEPT_DIGIT.at(bct_trybble_b) == '3');

    assert(termite::BCT_TRYBBLE_AND.at(bct_trybble_a).at(bct_trybble_b) == 0b00'01'00);
    assert(termite::BCT_TRYBBLE_OR.at(bct_trybble_a).at(bct_trybble_b) == 0b01'10'10);
    assert(termite::BCT_TRYBBLE_XOR.at(bct_trybble_a).at(bct_trybble_b) == 0b01'00'10);

    std::cout << "test_tables: All tests succeeded" << '\n';
}


void test_trybble() {
    termite::Trybble trybble_a(0b01'01'10); // decimal 14, sept E, ternary 112
    termite::Trybble trybble_b(termite::native_int, 20); // decimal 20, sept K, ternary 202
    termite::Trybble trybble_c(termite::sept, 'A'); // decimal 10, sept A, ternary 101

    // 112
    // 202

    assert(static_cast<char>(trybble_a & trybble_b) == 'B');
    assert(static_cast<char>(trybble_a | trybble_b) == 'N');
    assert(static_cast<char>(trybble_a ^ trybble_b) == '4');

    assert(static_cast<char>(trybble_a & trybble_c) == 'A');
    assert(static_cast<char>(trybble_a | trybble_c) == 'E');
    assert(static_cast<char>(trybble_a ^ trybble_c) == 'L');

    assert(static_cast<char>(trybble_b & trybble_c) == 'A');
    assert(static_cast<char>(trybble_b | trybble_c) == 'K');
    assert(static_cast<char>(trybble_b ^ trybble_c) == '0');

    assert(static_cast<char>(~trybble_a) == 'C');
    assert(trybble_a.get_bct() == 0b01'01'10);
    assert(static_cast<unsigned int>(trybble_a) == 14);
    assert(static_cast<char>(trybble_a) == 'E');

    assert(static_cast<char>(~trybble_b) == '6');
    assert(trybble_b.get_bct() == 0b10'00'10);
    assert(static_cast<unsigned int>(trybble_b) == 20);
    assert(static_cast<char>(trybble_b) == 'K');

    assert(static_cast<char>(~trybble_c) == 'G');
    assert(trybble_c.get_bct() == 0b01'00'01);
    assert(static_cast<unsigned int>(trybble_c) == 10);
    assert(static_cast<char>(trybble_c) == 'A');

    std::cout << "test_trybble: All tests succeeded" << '\n';
}

void test_tryte() {
    termite::Tryte tryte_a(termite::Trybble(termite::sept, '4'), termite::Trybble(termite::sept, 'D')); // decimal 121, sept 4D, ternary 011111
    termite::Tryte tryte_b(termite::Trybble(termite::sept, '6'), termite::Trybble(termite::sept, 'Q')); // decimal 188, sept 6Q, ternary 020222
    termite::Tryte tryte_c(termite::Trybble::ZERO, termite::Trybble::ONE); // decimal 1, sept 01, ternary 000001

    assert(static_cast<std::string>(tryte_a & tryte_b) == "3D");
    assert(static_cast<std::string>(tryte_a | tryte_b) == "7Q");
    assert(static_cast<std::string>(tryte_a ^ tryte_b) == "10");

    assert(static_cast<std::string>(tryte_a & tryte_c) == "01");
    assert(static_cast<std::string>(tryte_a | tryte_c) == "4D");
    assert(static_cast<std::string>(tryte_a ^ tryte_c) == "4E");

    assert(static_cast<std::string>(tryte_b & tryte_c) == "01");
    assert(static_cast<std::string>(tryte_b | tryte_c) == "6Q");
    assert(static_cast<std::string>(tryte_b ^ tryte_c) == "6O");

    assert(static_cast<std::string>(~tryte_a) == "MD");
    assert(static_cast<char>(tryte_a.get_hi()) == '4');
    assert(static_cast<char>(tryte_a.get_lo()) == 'D');
    assert(static_cast<unsigned int>(tryte_a) == 121);
    assert(static_cast<std::string>(tryte_a) == "4D");

    assert(static_cast<std::string>(~tryte_b) == "K0");
    assert(static_cast<char>(tryte_b.get_hi()) == '6');
    assert(static_cast<char>(tryte_b.get_lo()) == 'Q');
    assert(static_cast<unsigned int>(tryte_b) == 188);
    assert(static_cast<std::string>(tryte_b) == "6Q");

    assert(static_cast<std::string>(~tryte_c) == "QP");
    assert(static_cast<char>(tryte_c.get_hi()) == '0');
    assert(static_cast<char>(tryte_c.get_lo()) == '1');
    assert(static_cast<unsigned int>(tryte_c) == 1);
    assert(static_cast<std::string>(tryte_c) == "01");

    std::cout << "test_tryte: All tests succeeded" << '\n';
}

void test_word() {
}

void test_mem(termite::Mem &mem) {
}

void test_mov(termite::CPU &cpu) {
}

void test_add(termite::CPU &cpu) {
}

void test_sub(termite::CPU &cpu) {
}

void test_mul(termite::CPU &cpu) {
}

void test_umul(termite::CPU &cpu) {
}

void test_div(termite::CPU &cpu) {
}


int main() {
    termite::CPU cpu;

    test_tables();
    test_trybble();
    test_tryte();    
    // test_word();
    // test_mem(cpu.mem);    
    // test_mov(cpu);
    // test_add(cpu);
    // test_sub(cpu);
    // test_mul(cpu);

    return 0;
} 