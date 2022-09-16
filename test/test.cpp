#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/trybble.hpp"


void test_trybble() {
    termite::Trybble x(termite::from_int, -5);

    assert(x.get_bct() == 0b00'10'10);
    assert(x.to_int() == -5);
    assert(x.to_ternary_str() == "T11");
    assert(x.to_sept_digit() == 'M');
}

int main() {
    test_trybble();

    return 0;
}