#if !defined(TABLES_HPP)
#define TABLES_HPP

#include <string>
#include <map>

namespace termite {
    const std::map<int8_t, uint8_t> INT_TO_BCT_TRYBBLE{
        {-13, 0b00'00'00}, // TTT
        {-12, 0b00'00'01}, // TT0
        {-11, 0b00'00'10}, // TT1
        {-10, 0b00'01'00}, // T0T
        {-9, 0b00'01'01}, // T00
        {-8, 0b00'01'10}, // T01
        {-7, 0b00'10'00}, // T1T
        {-6, 0b00'10'01}, // T10
        {-5, 0b00'10'10}, // T11
        {-4, 0b01'00'00}, // 0TT
        {-3, 0b01'00'01}, // 0T0
        {-2, 0b01'00'10}, // 0T1
        {-1, 0b01'01'00}, // 00T
        {0, 0b01'01'01}, // 000
        {1, 0b01'01'10}, // 001
        {2, 0b01'10'00}, // 01T
        {3, 0b01'10'01}, // 010
        {4, 0b01'10'10}, // 011
        {5, 0b10'00'00}, // 1TT
        {6, 0b10'00'01}, // 1T0
        {7, 0b10'00'10}, // 1T1
        {8, 0b10'01'00}, // 10T
        {9, 0b10'01'01}, // 100
        {10, 0b10'01'10}, // 101
        {11, 0b10'10'00}, // 11T
        {12, 0b10'10'01}, // 110
        {13, 0b10'10'10} // 111
    };

    const std::map<uint8_t, int8_t> BCT_TRYBBLE_TO_INT{
        {0b00'00'00, -13}, // TTT
        {0b00'00'01, -12}, // TT0
        {0b00'00'10, -11}, // TT1
        {0b00'01'00, -10}, // T0T
        {0b00'01'01, -9}, // T00
        {0b00'01'10, -8}, // T01
        {0b00'10'00, -7}, // T1T
        {0b00'10'01, -6}, // T10
        {0b00'10'10, -5}, // T11
        {0b01'00'00, -4}, // 0TT
        {0b01'00'01, -3}, // 0T0
        {0b01'00'10, -2}, // 0T1
        {0b01'01'00, -1}, // 00T
        {0b01'01'01, 0}, // 000
        {0b01'01'10, 1}, // 001
        {0b01'10'00, 2}, // 01T
        {0b01'10'01, 3}, // 010
        {0b01'10'10, 4}, // 011
        {0b10'00'00, 5}, // 1TT
        {0b10'00'01, 6}, // 1T0
        {0b10'00'10, 7}, // 1T1
        {0b10'01'00, 8}, // 10T
        {0b10'01'01, 9}, // 100
        {0b10'01'10, 10}, // 101
        {0b10'10'00, 11}, // 11T
        {0b10'10'01, 12}, // 110
        {0b10'10'10, 13} // 111
    };

    const std::map<uint8_t, std::string> BCT_TRYBBLE_TO_TERNARY_STR{
        {0b00'00'00, "TTT"},
        {0b00'00'01, "TT0"},
        {0b00'00'10, "TT1"},
        {0b00'01'00, "T0T"},
        {0b00'01'01, "T00"},
        {0b00'01'10, "T01"},
        {0b00'10'00, "T1T"},
        {0b00'10'01, "T10"},
        {0b00'10'10, "T11"},
        {0b01'00'00, "0TT"},
        {0b01'00'01, "0T0"},
        {0b01'00'10, "0T1"},
        {0b01'01'00, "00T"},
        {0b01'01'01, "000"},
        {0b01'01'10, "001"},
        {0b01'10'00, "01T"},
        {0b01'10'01, "010"},
        {0b01'10'10, "011"},
        {0b10'00'00, "1TT"},
        {0b10'00'01, "1T0"},
        {0b10'00'10, "1T1"},
        {0b10'01'00, "10T"},
        {0b10'01'01, "100"},
        {0b10'01'10, "101"},
        {0b10'10'00, "11T"},
        {0b10'10'01, "110"},
        {0b10'10'10, "111"}
    };

    const std::map<uint8_t, int8_t> BCT_TRYBBLE_TO_SEPT_DIGIT{
        {0b00'00'00, 'E'}, // TTT
        {0b00'00'01, 'F'}, // TT0
        {0b00'00'10, 'G'}, // TT1
        {0b00'01'00, 'H'}, // T0T
        {0b00'01'01, 'I'}, // T00
        {0b00'01'10, 'J'}, // T01
        {0b00'10'00, 'K'}, // T1T
        {0b00'10'01, 'L'}, // T10
        {0b00'10'10, 'M'}, // T11
        {0b01'00'00, 'N'}, // 0TT
        {0b01'00'01, 'O'}, // 0T0
        {0b01'00'10, 'P'}, // 0T1
        {0b01'01'00, 'Q'}, // 00T
        {0b01'01'01, '0'}, // 000
        {0b01'01'10, '1'}, // 001
        {0b01'10'00, '2'}, // 01T
        {0b01'10'01, '3'}, // 010
        {0b01'10'10, '4'}, // 011
        {0b10'00'00, '5'}, // 1TT
        {0b10'00'01, '6'}, // 1T0
        {0b10'00'10, '7'}, // 1T1
        {0b10'01'00, '8'}, // 10T
        {0b10'01'01, '9'}, // 100
        {0b10'01'10, 'A'}, // 101
        {0b10'10'00, 'B'}, // 11T
        {0b10'10'01, 'C'}, // 110
        {0b10'10'10, 'D'} // 111
    };
} // namespace termite

#endif // TABLES_HPP