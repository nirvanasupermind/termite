#include <iostream>
#include <cassert>
#include <string>

#include "../src/tables.hpp"
#include "../src/trybble.hpp"

void test_tables() {
    uint8_t bct1 = 0b01'01'00; // 110
    uint8_t bct2 = 0b10'00'00; // 200
    
    assert(termite::BCT_TRYBBLE_TO_TERNARY_STR.at(bct1) == "110");
    assert(termite::BCT_TRYBBLE_TO_SEPT_CHAR.at(bct1) == 'C');
    assert(termite::BCT_TRYBBLE_AND.at(bct1).at(bct2) == 0b01'00'00); // 100
    assert(termite::BCT_TRYBBLE_OR.at(bct1).at(bct2) == 0b10'01'00); // 210
    assert(termite::BCT_TRYBBLE_XOR.at(bct1).at(bct2) == 0b00'01'00); // 010
}

void test_trybble() {
    termite::Trybble trybble1(0b10'00'01); // 201
    termite::Trybble trybble2(0b00'00'10); // 002

    assert((trybble1 & trybble2).to_ternary_str() == "001");
    assert((trybble1 | trybble2).to_ternary_str() == "202");
    assert((trybble1 ^ trybble2).to_ternary_str() == "200");
    assert(trybble1.to_i8() == -8);
    assert(trybble1.to_u8() == 19);
    assert(trybble1.to_ternary_str() == "201");
    assert(trybble1.to_sept_char() == 'J');
}

int main() {
    test_tables();
    std::cout << "test_tables succeeded" << '\n';

    test_trybble();
    std::cout << "test_trybble succeeded" << '\n';
    return 0;
}