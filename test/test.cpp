#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/trybble.hpp"

int main() {
    termite::Trybble x(termite::from_val, 5);
    termite::Trybble y(termite::from_val, 6);

    assert(x.to_uint8_t() == 5);
    assert(y.to_uint8_t() == 6);
    assert((x + y).to_uint8_t() == 11);

    return 0;
}