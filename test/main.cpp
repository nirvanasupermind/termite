#include <iostream>
#include "../src/tryte.h"

int main() {
    termite::Tryte t(0b0110);
    std::cout << (int)t.get_trit(0) << '\n';
}