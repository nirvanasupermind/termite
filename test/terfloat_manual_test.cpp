#include <iostream>
#include <string>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/core/terfloat.h"

int main() {
    termite::TerFloat x = termite::TerFloat::from_double(2.0);
    // termite::TerFloat y = termite::TerFloat::from_double(2.1);
    

        // std::cout << (termite::Word::from_int32(-33) / termite::Word::from_int32(2)).to_int32() << '\n';

    std::cout << (x > termite::TerFloat::ONE) << '\n';
    std::cout << (x < termite::TerFloat::from_double(-3.0)) << '\n';

        // std::cout << x.log().operator-().exp().to_str() << '\n';

}