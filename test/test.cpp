#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/trybble.hpp"

void test() {
    termite::Trybble x(termite::from_val, 5);
    termite::Trybble y(termite::from_val, 25);

    assert(x.to_int8_t() == 5);
    assert(y.to_int8_t() == -2);
    assert((x * y).to_int8_t() == -10);
}

int main() {
    test();

    return 0;
}