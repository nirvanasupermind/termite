#include <iostream>
#include "../src/tryte.h"
#include "../src/tcs.h"

int main() {
    termite::Tryte tryte1 = termite::Tryte::from_bct(0b10'01'10);
    std::cout << tryte1.to_int() << '\n';
    return 0;
}