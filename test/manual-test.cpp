#include <iostream>
#include <array>

#include "../src/trit.h"
#include "../src/tryte.h"

int main() 
{   
    termite::Tryte x({std::array<termite::Trit, 6> {0, 0, 0, 1, 0, -1}});
    termite::Tryte y({std::array<termite::Trit, 6> {0, 0, 0, 0, 1, 0}});

    std::cout << (x * y).to_str() << '\n'; // 0010Z0
}