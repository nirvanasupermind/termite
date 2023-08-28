#include <iostream>
#include "../src/word.h"

int main() {
    termite::Word x = termite::Word::from_int32(5);
    std::cout << (x*termite::Word::from_int32(394)).to_int32() << '\n';
}