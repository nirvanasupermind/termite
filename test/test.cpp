#include <iostream>
#include <cassert>
#include <string>

#include "../src/tables.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"
#include "../src/word.hpp"

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
    termite::Trybble trybble2 = termite::Trybble::from_i8(2); // 002

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
    termite::Tryte tryte1 = termite::Tryte::from_i16(41); // 001112
    termite::Tryte tryte2(termite::Trybble(0b10'10'10), termite::Trybble(0b10'10'00)); // 222220

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
    termite::Word word1 = termite::Word::from_i32(1984); // 000000000002201111
    termite::Word word2 = termite::Word::from_i32(-504); // 222222222222022100

    // 000000000002201111
    // 222222222222022100
    // 222222222221220211

    assert((word1 + word2).to_i32() == 1480);
    assert((word1 - word2).to_i32() == 2488);
    assert((word1 * word2).to_i32() == -999936);
    assert((word1.mulu(word2)).to_u32() == 386420553);
    assert((word1 / word2).to_i32() == -3);
    assert((word1.divu(word2)).to_u32() == 0);
    assert((word1 % word2).to_i32() == 472);
    assert((word1.modu(word2)).to_u32() == 1984);
    assert((-word1).to_i32() == -1984);
    assert((word1 & word2).to_ternary_str() == "000000000002001100");
    assert((word1 | word2).to_ternary_str() == "222222222222222111");
    assert((word1 ^ word2).to_ternary_str() == "222222222221220211");
    assert(word1.get_hi().to_i16() == 0); 
    assert(word1.get_mid().to_i16() == 2); 
    assert(word1.get_lo().to_i16() == -203);
    assert(word1.to_i32() == 1984);
    assert(word2.to_i32() == -504);
    assert(word1.to_u32() == 1984);
    assert(word2.to_u32() == 387419985);    
    assert(word1.to_ternary_str() == "000000000002201111");
    assert(word1.to_sept_str() == "0002JD");
}

int main() {
    test_tables();
    std::cout << "test_tables succeeded" << '\n';

    test_trybble();
    std::cout << "test_trybble succeeded" << '\n';
    
    test_tryte();
    std::cout << "test_tryte succeeded" << '\n';
    
    test_word();
    std::cout << "test_word succeeded" << '\n';

    return 0;
}