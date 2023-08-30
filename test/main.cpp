#include <iostream>
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/mem.h"

int main() {
    termite::Mem mem;
    mem.load_bct_file("test/bctfile");
    std::cout << mem.get_word(termite::Word::from_int32(-21523360)).to_int32() << '\n';
}