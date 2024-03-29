// Lookup tables and etc. for text processing

#ifndef TEXT_H
#define TEXT_H
#include <string>

namespace termite {
    std::vector<wchar_t> CHAR_ENCODING_LIST = {
        '\0',
        '\a',
        '\b',
        '\t',
        '\n',
        '\v',
        '\f',
        '\r',
        '\u001B',
        ' ',
        '-',
        ':',
        ';',
        '\'',
        ',',
        '.',
        '?',
        '!',
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '_',
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z'      
    };
} // namespace termite

#endif // TEXT_H