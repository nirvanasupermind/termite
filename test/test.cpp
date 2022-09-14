#include <iostream>
#include <cassert>

#include "../src/util.hpp"
#include "../src/word.hpp"

void test() {
    termite::Word x(termite::from_val, -7398);
    termite::Word y(termite::from_val, 6);

    assert((x * y).to_int32_t() == -44388);
    assert((x - ~y).to_int32_t() == -7392);
    assert((x - ~y).to_hept_str() == "0QW6");
    assert((x & y).to_int32_t() == -7401);
    assert((x & y).to_hept_str() == "0QWX");
}

int main() {
    test();

    return 0;
}