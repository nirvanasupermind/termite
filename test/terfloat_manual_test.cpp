#include <iostream>
#include <string>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/core/terfloat.h"

int main() {
    termite::TerFloat x = termite::TerFloat::from_double(9872.0);
    // termite::TerFloat y = termite::TerFloat::from_double(2.1);
    

    std::cout << (x % termite::TerFloat::from_double(2 * M_PI)).to_str() << '\n';

}