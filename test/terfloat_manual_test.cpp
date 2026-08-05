#include <iostream>
#include <string>

#include "../src/core/tryte.h"
#include "../src/core/word.h"

int main() {
    std::cerr << "entered main\n";

    termite::Word x = termite::Word::from_int32(10000);
    termite::Word y = termite::Word::from_int32(20000);

    std::cerr << "before mul32\n";
    auto result = x.mul32(y);
    std::cerr << "after mul32\n";

    std::cout << result.first.to_int32() << '\n';
    std::cout << result.second.to_int32() << '\n';
}

// int main() {
//     termite::Word x = termite::Word::from_int32(10000);
//     termite::Word y = termite::Word::from_int32(20000);
    

//     auto result = x.mul32(y);

//     std::cout << result.first.to_int32() << '\n';
//     std::cout << result.second.to_int32() << '\n';


// }