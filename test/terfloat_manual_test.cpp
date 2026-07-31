#include <iostream>
#include <string>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/core/terfloat.h"

int main() {
    termite::Word x = termite::Word::from_int32(10000);
    termite::Word y = termite::Word::from_int32(20000);
    

    auto result = x.mul32(y);

    std::cout << result.first.to_int32() << '\n';
    std::cout << result.second.to_int32() << '\n';


}