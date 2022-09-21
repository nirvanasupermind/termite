#include <iostream>
#include <cassert>
#include <string>

#include "../src/util.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"


void test_trybble() {
    termite::Trybble x(-5);
    termite::Trybble y(3);

    assert((x & y).to_int() == -6);
    assert((x | y).to_int() == 4);
    assert(x.get_bct() == 0b00'10'10);
    assert(x.to_int() == -5);
    assert(x.to_ternary_str() == "T11");
    assert(x.to_sept_digit() == 'M');
}

void test_tryte() {
    termite::Tryte x(45);
    termite::Tryte y(-13);

    assert((x & y).to_int() == -40);
    assert((x | y).to_int() == 72);
    assert(x.get_hi().to_int() == 2);
    assert(x.get_lo().to_int() == -9);
    assert(x.to_int() == 45);
    assert(x.to_ternary_str() == "01TT00");
    assert(x.to_sept_str() == "2I");
}


int main() {
    test_trybble();
    std::cout << "All trybble tests succeeded" << '\n';

    test_tryte();
    std::cout << "All tryte tests succeeded" << '\n';
    return 0;
}