#include <iostream>
#include <string>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/core/terfloat.h"

int main() {
    termite::TerFloat x = termite::TerFloat::from_double(3.0);
    termite::TerFloat y = termite::TerFloat::from_double(3.0);
    
    
    std::cout << (x / termite::TerFloat::from_double(49.9)).to_str() << '\n';

}