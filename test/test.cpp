#include <iostream>
#include "../src/tryte.h"
#include "../src/word.h"

int main() {
    termite::Word word1 = termite::Word::from_int(505);
    termite::Word word2 = termite::Word::from_int(30);

    std::cout << (word1 * word2).to_int() << '\n';
    return 0;
}