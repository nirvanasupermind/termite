#include <iostream>
#include <array>

#include "../src/trit.h"
#include "../src/tryte.h"

int main() 
{   
    // termite::Tryte x({std::array<termite::Trit, 6> {0, 0, 0, 1, 0, -1}});
    termite::Tryte x({std::array<termite::Trit, 6> {0, 0, 0, 0, 1, 0}});
    termite::Tryte y({std::array<termite::Trit, 6> {0, 1, 1, 0, -1, 0}});

    std::cout << y.to_hept() << '\n'; // 0010Z0
}