#include <iostream>
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/mem.h"

int main() {
    termite::Mem mem;
    mem.set_word(0, termite::Word::from_int32(10000));
    std::cout << mem.get_word(0).str() << '\n';
}