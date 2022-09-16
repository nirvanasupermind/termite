#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/trybble.hpp"
#include "../src/tryte.hpp"


void test_trybble() {
    termite::Trybble x(-5);

    assert(x.get_bct() == 0b00'10'10);
    assert(x.to_int() == -5);
    assert(x.to_ternary_str() == "T11");
    assert(x.to_sept_digit() == 'M');
}

void test_tryte() {
    termite::Tryte x(45);

    assert(x.get_hi().to_int() == 2);
    assert(x.get_lo().to_int() == -9);
    assert(x.to_int() == 45);
    assert(x.to_ternary_str() == "01TT00");
    assert(x.to_sept_str() == "2I");
}

int main() {
    test_trybble();
    test_tryte();

    return 0;
}