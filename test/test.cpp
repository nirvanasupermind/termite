#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/tryte.hpp"

void test() {
    termite::Tryte x(termite::from_val, 164);
    termite::Tryte y(termite::from_val, -2);

    assert(x.to_int16_t() == 164);
    assert(y.to_int16_t() == -2);
    assert((x * y).to_int16_t() == -328);
    assert((x * y).to_hept_str() == "OW");
}

int main() {
    test();

    return 0;
}