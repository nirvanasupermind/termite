// -*- core/tce.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TCE_H
#define TCE_H

#include <cstdint>
#include <map>

#include "tryte.h"


namespace termite
{
    // The Termite Character Encoding (TCE) is an character encoding which encodes 729 characters as unique trytes.
    // It contains 9 blocks, each of which has 3 sub-blocks.
    // This file provides several lookup tables for conversion to and from TCE.

    std::map<int16_t, char16_t> tce_to_char {
        /////////////////////////////////////////
        // Block 0: Latin-A
        // Sub-Block 0: Punctuation & Symbols A
        {0, '\0'}, // Null character
        {1, '\a'}, // Bell character
        {2, '\b'}, // Backspace
        {3, '\t'}, // Horizontal tab
        {4, '\n'}, // Line feed
        {5, '\v'}, // Vertical tab
        {6, '\f'}, // Form feed
        {7, '\r'}, // Carriage return
        {8, '\x1A'}, // End-of-file
        {9, ' '}, // Space
        {10, '+'}, // Plus sign
        {11, '-'}, // Minus sign
        {12, '.'}, // Period
        {13, '!'}, // Exclamation mark
        {14, '?'}, // Question mark
        {15, ','}, // Comma
        {16, '"'}, // Quotation mark
        {17, '\''}, // Apostrophe
        {18, '0'}, // Digit zero
        {19, '1'}, // Digit one
        {20, '2'}, // Digit two
        {21, '3'}, // Digit three
        {22, '4'}, // Digit four
        {23, '5'}, // Digit five
        {24, '6'}, // Digit six
        {25, '7'}, // Digit seven
        {26, '8'}, // Digit eight
        // Sub-Block 1: Uppercase Latin Alphabet
        {27, '9'}, // Digit nine
        {28, 'A'}, // Latin uppercase letter A
        {29, 'B'}, // Latin uppercase letter B
        {30, 'C'}, // Latin uppercase letter C
        {31, 'D'}, // Latin uppercase letter D
        {32, 'E'}, // Latin uppercase letter E
        {33, 'F'}, // Latin uppercase letter F
        {34, 'G'}, // Latin uppercase letter G
        {35, 'H'}, // Latin uppercase letter H
        {36, 'I'}, // Latin uppercase letter I
        {37, 'J'}, // Latin uppercase letter J
        {38, 'K'}, // Latin uppercase letter K
        {39, 'L'}, // Latin uppercase letter L
        {40, 'M'}, // Latin uppercase letter M
        {41, 'N'}, // Latin uppercase letter N
        {42, 'O'}, // Latin uppercase letter O
        {43, 'P'}, // Latin uppercase letter P
        {44, 'Q'}, // Latin uppercase letter Q
        {45, 'R'}, // Latin uppercase letter R
        {46, 'S'}, // Latin uppercase letter S
        {47, 'T'}, // Latin uppercase letter T
        {48, 'U'}, // Latin uppercase letter U
        {49, 'V'}, // Latin uppercase letter V
        {50, 'W'}, // Latin uppercase letter W
        {51, 'X'}, // Latin uppercase letter W
        {52, 'Y'}, // Latin uppercase letter Y
        {53, 'Z'}, // Latin uppercase letter Z
        // Sub-Block 2: Lowercase Latin Alphabet
        {54, '_'}, // Underscore
        {55, 'a'}, // Latin lowercase letter A
        {56, 'b'}, // Latin lowercase letter B
        {57, 'c'}, // Latin lowercase letter C
        {58, 'd'}, // Latin lowercase letter D
        {59, 'e'}, // Latin lowercase letter E
        {60, 'f'}, // Latin lowercase letter F
        {61, 'g'}, // Latin lowercase letter G
        {62, 'h'}, // Latin lowercase letter H
        {63, 'i'}, // Latin lowercase letter I
        {64, 'j'}, // Latin lowercase letter J
        {65, 'k'}, // Latin lowercase letter K
        {66, 'l'}, // Latin lowercase letter L
        {67, 'm'}, // Latin lowercase letter M
        {68, 'n'}, // Latin lowercase letter N
        {69, 'o'}, // Latin lowercase letter O
        {70, 'p'}, // Latin lowercase letter P
        {71, 'q'}, // Latin lowercase letter Q
        {72, 'r'}, // Latin lowercase letter R
        {73, 's'}, // Latin lowercase letter S
        {74, 't'}, // Latin lowercase letter T
        {75, 'u'}, // Latin lowercase letter U
        {76, 'v'}, // Latin lowercase letter V
        {77, 'w'}, // Latin lowercase letter W
        {78, 'x'}, // Latin lowercase letter W
        {79, 'y'}, // Latin lowercase letter Y
        {80, 'z'}, // Latin lowercase letter Z
        /////////////////////////////////////////
        // Block 1: Latin-B
        // Sub-Block 3: Punctuation & Symbols B        
        {81, '*'}, // Asterisk
        {82, '/'}, // Slash
        {83, '|'}, // Vertical bar
        {84, '\\'}, // Backslash
        {85, '<'}, // Less-than sign
        {86, '='}, // Equals sign
        {87, '>'}, // Greater sign
        {88, 0xd7}, // Multiplication sign
        {89, 0xf7}, // Division sign
        {90, '#'}, // Number sign
        {91, '$'}, // Dollar sign
        {92, '%'}, // Percent sign
        {93, '('}, // Left parenthesis
        {94, ')'}, // Right parenthesis
        {95, '['}, // Left square bracket
        {96, ']'}, // Right square bracket
        {97, '{'}, // Left curly bracket
        {98, '}'}, // Right curly bracket
        {99, '^'}, // Circumflex accent
        {100, '`'}, // Grave accent
        {101, '~'}, // Tilde
        {102, 0xa1}, // Inverted exclamation mark
        {103, 0xbf}, // Inverted question mark
        {104, 0xb0}, // Degree sign
        {105, 0xb1}, // Plus-minus sign   
        {106, 0xb2}, // Superscript two
        {107, 0xb3}, // Superscript three
        // Sub-Block 4: Uppercase Latin-B
        {108, 0xc0}, // Latin uppercase letter A with grave
        {109, 0xc1}, // Latin uppercase letter A with acute
        {110, 0xc2}, // Latin uppercase letter A with circumflex
        {111, 0xc4}, // Latin uppercase letter A with diaeresis        
        {112, 0xc5}, // Latin uppercase letter A with ring above        
        {113, 0xc6}, // Latin uppercase letter AE
        {114, 0xc7}, // Latin uppercase letter C with cedilla
        {115, 0xc8}, // Latin uppercase letter E with grave
        {116, 0xc9}, // Latin uppercase letter E with acute
        {117, 0xca}, // Latin uppercase letter E with circumflex
        {118, 0xcb}, // Latin uppercase letter E with diaeresis
        {119, 0xcc}, // Latin uppercase letter I with grave
        {120, 0xcd}, // Latin uppercase letter I with acute
        {121, 0xce}, // Latin uppercase letter I with circumflex
        {122, 0xcf}, // Latin uppercase letter I with diaeresis
        {123, 0xd0}, // Latin uppercase letter Eth
        {124, 0xd1}, // Latin uppercase letter N with tilde
        {125, 0xd2}, // Latin uppercase letter O with grave
        {126, 0xd3}, // Latin uppercase letter O with acute
        {127, 0xd4}, // Latin uppercase letter O with circumflex
        {128, 0xd5}, // Latin uppercase letter O with diaeresis
        {129, 0xd6}, // Latin uppercase letter O with stroke
        {129, 0xd9}, // Latin uppercase letter U with grave        
        {130, 0xda}, // Latin uppercase letter U with acute
        {131, 0xdb}, // Latin uppercase letter U with circumflex
        {132, 0xdc}, // Latin uppercase letter U with diaeresis
        {133, 0xdd}, // Latin uppercase letter Y with acute
        {134, 0xde}, // Latin uppercase letter Thorn
    };

} // namespace termite

#endif // TCE_H