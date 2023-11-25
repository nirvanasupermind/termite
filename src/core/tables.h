#ifndef TABLES_H
#define TABLES_H
#include <cstdint>

namespace termite {
    const int32_t POW3[16] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907 };

    // Trit gate lookup tables
    // Note that this is using the BCT encodings of the trits (0b00,0b01,0b10 or 0,1,2) 
    // rather than actual values (-1,0,1)
    const uint8_t TRIT_NOT[3] = { 2,1,0 };
    const uint8_t TRIT_AND[3][3] = { {0,0,0},{0,1,1},{0,1,2} };
    const uint8_t TRIT_OR[3][3] = { {0,1,2},{1,1,2},{2,2,2} };
    const uint8_t TRIT_XOR[3][3] = { {0,1,2},{1,2,0},{2,0,1} };
    const uint8_t TRIT_SUM[3][3][3] = { {{1,2,0},{2,0,1},{0,1,2}},{{2,0,1},{0,1,2},{1,2,0}},{{0,1,2},{1,2,0},{2,0,1}} };
    const uint8_t TRIT_CARRY[3][3][3] = { {{0,0,1},{0,1,1},{1,1,1}},{{0,1,1},{1,1,1},{1,1,2}},{{1,1,1},{1,1,2},{1,2,2}} };

}

#endif // TABLES_H