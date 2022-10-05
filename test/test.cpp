#include <iostream>
#include <cassert>
#include <string>

#include "../src/tables.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"
#include "../src/word.hpp"
#include "../src/mem.hpp"
#include "../src/cpu.hpp"

void test_tables() {
    uint8_t bct1 = 0b01'01'00; // 110
    uint8_t bct2 = 0b10'00'00; // 200
    
    assert(termite::BCT_TRYBBLE_TO_TERNARY_STR.at(bct1) == "110");
    assert(termite::BCT_TRYBBLE_TO_SEPT_CHAR.at(bct1) == 'C');
    assert(termite::BCT_TRYBBLE_AND.at(bct1).at(bct2) == 0b01'00'00); // ter 100
    assert(termite::BCT_TRYBBLE_OR.at(bct1).at(bct2) == 0b10'01'00); // ter 210
    assert(termite::BCT_TRYBBLE_XOR.at(bct1).at(bct2) == 0b00'01'00); // ter 010
}

void test_trybble() {
    termite::Trybble trybble1(0b10'00'01); // dec -8, ter 201
    termite::Trybble trybble2 = termite::Trybble::from_i8(2); // ter 002

    assert((trybble1 & trybble2).to_ternary_str() == "001");
    assert((trybble1 | trybble2).to_ternary_str() == "202");
    assert((trybble1 ^ trybble2).to_ternary_str() == "200");
    assert((~trybble1).to_ternary_str() == "021");
    assert(trybble1.to_i8() == -8);
    assert(trybble1.to_u8() == 19);
    assert(trybble1.to_ternary_str() == "201");
    assert(trybble1.to_sept_char() == 'J');
}

void test_tryte() {
    termite::Tryte tryte1 = termite::Tryte::from_i16(41); // ter 001112
    termite::Tryte tryte2(termite::Trybble(0b10'10'10), termite::Trybble(0b10'10'00)); // dec -3, ter 222220

    assert((tryte1 & tryte2).to_ternary_str() == "001110");
    assert((tryte1 | tryte2).to_ternary_str() == "222222");
    assert((tryte1 ^ tryte2).to_ternary_str() == "220002");
    assert(tryte1.get_hi().to_i8() == 1); 
    assert(tryte1.get_lo().to_i8() == -13);
    assert(tryte1.to_i16() == 41);
    assert(tryte2.to_i16() == -3);    
    assert(tryte1.to_u16() == 41);
    assert(tryte2.to_u16() == 726);    
    assert(tryte1.to_ternary_str() == "001112");
    assert(tryte1.to_sept_str() == "1E");
}

void test_word() {
    termite::Word word1 = termite::Word::from_sept_str("02JD"); // dec 1984, ter 0000002201111
    termite::Word word2 = termite::Word::from_i32(-504); // ter 2222222022100

    // 000000000002201111
    // 222222222222022100
    // 222222222221220211

    assert((word1 + word2).to_i32() == 1480);
    assert((word1 - word2).to_i32() == 2488);
    assert((word1 * word2).to_i32() == 62946);
    assert((word1.umul(word2)).to_u32() == 62946);
    assert((word1 / word2).to_i32() == -3);
    assert((word1.udiv(word2)).to_u32() == 0);
    assert((word1 % word2).to_i32() == 472);
    assert((word1.umod(word2)).to_i32() == 1984);
    assert((-word1).to_i32() == -1984);
    assert((word1 & word2).to_ternary_str() == "000002001100");
    assert((word1 | word2).to_ternary_str() == "222222222111");
    assert((word1 ^ word2).to_ternary_str() == "222221220211");
    assert(word1.get_hi().to_u16() == 2); 
    assert(word1.get_lo().to_u16() == 526);
    assert(word1.to_i32() == 1984);
    assert(word2.to_i32() == -504);
    assert(word1.to_u32() == 1984);
    assert(word2.to_u32() == 530937);    
    assert(word1.to_ternary_str() == "000002201111");
    assert(word1.to_sept_str() == "02JD");
}

void test_mem(termite::Mem &mem) {
    mem.write_tryte(termite::Word::ONE, termite::Tryte::ONE);
    mem.write_tryte(termite::Word::TWO, termite::Tryte::from_i16(360));

    assert(mem.read_tryte(termite::Word::ONE).to_i16() == 1);
    assert(mem.read_word(termite::Word::ONE).to_i32() == 1089);
}

void test_mov(termite::CPU &cpu) {
    termite::Word i = termite::Word::from_i32(-2);

    // mov <abs>,<imm>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // 0s0100
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00"));
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); // #5
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("05"));

    // mov <abs>,<abs>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // 0s0101
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01"));
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // 0s0100
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00"));

    // mov <abs>,<reg>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("02")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // 0s0102
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("02"));
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); // r0

    // mov <reg>,<imm>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("03")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); // r0
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); // #12
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("0C"));

    // mov <reg>,<abs>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("04")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // r1
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("01")); // 0s0100
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("00")); 
    
    // mov <reg>,<reg>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("05")); // mov
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("21")); // r2, r1
    cpu.execute();

    // mov <reg>,<reg>
    cpu.mem.write_tryte(++i, termite::Tryte::from_sept_str("06")); // hlt
    cpu.execute();

    
    assert(cpu.mem.read_word(termite::Word::from_sept_str("0100")).to_i32() == 5);
    assert(cpu.mem.read_word(termite::Word::from_sept_str("0101")).to_i32() == 5);
    assert(cpu.mem.read_word(termite::Word::from_sept_str("0102")).to_i32() == 0);

    assert(cpu.register_file[0].to_i32() == 12);
    assert(cpu.register_file[1].to_i32() == 5);
    assert(cpu.register_file[2].to_i32() == 12);

    cpu.reset();
}

int main() {
    termite::CPU cpu;

    test_tables();
    std::cout << "test_tables succeeded" << '\n';

    test_trybble();
    std::cout << "test_trybble succeeded" << '\n';
    
    test_tryte();
    std::cout << "test_tryte succeeded" << '\n';
    
    test_word();
    std::cout << "test_word succeeded" << '\n';

    test_mem(cpu.mem);
    std::cout << "test_mem succeeded" << '\n';
    
    test_mov(cpu);
    std::cout << "test_mov succeeded" << '\n';

    return 0;
} 