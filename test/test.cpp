#include <iostream>
#include "../src/tryte.h"


int main() {
    termite::Tryte tryte1(40);
    termite::Tryte tryte2(-5);
    std::cout << "40 + (-5) = " << (tryte1 + tryte2).to_int() << '\n';
    std::cout << "40 - (-5) = " << (tryte1 - tryte2).to_int() << '\n';
    return 0;
}