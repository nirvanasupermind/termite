#ifndef TABLES_H
#define TABLES_H

#include <string>
#include <vector>
#include <map>

namespace termite {
    // Miscalleneous lookup tables

    const std::vector<int> POW3{
        1,
        3,
        9,
        27,
        81,
        243,
        729,
        2187,
        6561,
        19683,
        59049,
        177147,
        531441,
        1594323,
        4782969,
        14348907,
        43046721,
        129140163,
        387420489,
        1162261467
    };
    
    const std::map<int, wchar_t> CODEPOINT_TO_TCS_CHAR{
        // Block 0: Latin #1
        {0, 0}, // NUL
        {1, 7}, // BEL
        {2, 8}, // BS
        {3, '\t'}, // HT
    };
} // namespace termite

#endif // TABLES_H