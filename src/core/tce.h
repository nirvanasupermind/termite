// -*- core/tce.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef TCE_H
#define TCE_H

#include <map>

#include "tryte.h"


namespace termite
{
    // The Termite Character Encoding (TCE) is an character encoding which encodes 729 characters as unique trytes.
    // It contains 3 segments, each of which has 9 subsegments.
    // This file provides several lookup tables for conversion to and from TCE.

    std::map<std::string, char16_t> tce_to_char {
        // Segment 0: Latin
        // Subsegment 0: Punctuation & Symbols A
        {"00", '\0'}, // Null character
        {"01", '\a'}, // Bell character
        {"02", '\b'}, // Backspace
        {"03", '\t'}, // Horizontal tab
        {"04", '\n'}, // Line feed
        {"05", '\v'}, // Vertical tab
        {"06", '\f'}, // Form feed
        {"07", '\r'}, // Carriage return
        {"08", '\x1A'}, // End-of-file
        {"09", ' '}, // Space
        {"0a", '+'}, // Plus sign
        {"0b", '-'}, // Minus sign
        {"0c", '!'}, // Exclamation mark
        {"0d", '"'}, // Quotation mark
        {"0e", '\''}, // Apostrophe
        {"0f", ','}, // Comma
        {"0g", '.'}, // Period
        {"0h", '?'}, // Question mark
        {"0i", '0'}, // Digit zero
        {"0j", '1'}, // Digit one
        {"0k", '2'}, // Digit two
        {"0l", '3'}, // Digit three
        {"0m", '4'}, // Digit four
        {"0n", '5'}, // Digit five
        {"0o", '6'}, // Digit six
        {"0p", '7'}, // Digit seven
        {"0q", '8'}, // Digit eight
        // Subsegment 1: Uppercase Latin Alphabet
        {"10", '9'}, // Digit nine
        {"11", 'A'}, // Latin uppercase letter A
        {"12", 'B'}, // Latin uppercase letter B
        {"13", 'C'}, // Latin uppercase letter C
        {"14", 'D'}, // Latin uppercase letter D
        {"15", 'E'}, // Latin uppercase letter E
        {"16", 'F'}, // Latin uppercase letter F
        {"17", 'G'}, // Latin uppercase letter G
        {"18", 'H'}, // Latin uppercase letter H
        {"19", 'I'}, // Latin uppercase letter I
        {"1a", 'J'}, // Latin uppercase letter J
        {"1b", 'K'}, // Latin uppercase letter K
        {"1c", 'L'}, // Latin uppercase letter L
        {"1d", 'M'}, // Latin uppercase letter M
        {"1e", 'N'}, // Latin uppercase letter N
        {"1f", 'O'}, // Latin uppercase letter O
        {"1g", 'P'}, // Latin uppercase letter P
        {"1h", 'Q'}, // Latin uppercase letter Q
        {"1i", 'R'}, // Latin uppercase letter R
        {"1j", 'S'}, // Latin uppercase letter S
        {"1k", 'T'}, // Latin uppercase letter T
        {"1l", 'U'}, // Latin uppercase letter U
        {"1m", 'V'}, // Latin uppercase letter V
        {"1n", 'W'}, // Latin uppercase letter W
        {"1o", 'X'}, // Latin uppercase letter W
        {"1p", 'Y'}, // Latin uppercase letter Y
        {"1q", 'Z'}, // Latin uppercase letter Z
        // Subsegment 2: Lowercase Latin Alphabet
        {"20", 'a'}, // Underscore
        {"21", 'a'}, // Latin lowercase letter A
        {"22", 'b'}, // Latin lowercase letter B
        {"23", 'c'}, // Latin lowercase letter C
        {"24", 'd'}, // Latin lowercase letter D
        {"25", 'e'}, // Latin lowercase letter E
        {"26", 'f'}, // Latin lowercase letter F
        {"27", 'g'}, // Latin lowercase letter G
        {"28", 'h'}, // Latin lowercase letter H
        {"29", 'i'}, // Latin lowercase letter I
        {"2a", 'j'}, // Latin lowercase letter J
        {"2b", 'k'}, // Latin lowercase letter K
        {"2c", 'l'}, // Latin lowercase letter L
        {"2d", 'm'}, // Latin lowercase letter M
        {"2e", 'n'}, // Latin lowercase letter N
        {"2f", 'o'}, // Latin lowercase letter O
        {"2g", 'p'}, // Latin lowercase letter P
        {"2h", 'q'}, // Latin lowercase letter Q
        {"2i", 'r'}, // Latin lowercase letter R
        {"2j", 's'}, // Latin lowercase letter S
        {"2k", 't'}, // Latin lowercase letter T
        {"2l", 'u'}, // Latin lowercase letter U
        {"2m", 'v'}, // Latin lowercase letter V
        {"2n", 'w'}, // Latin lowercase letter W
        {"2o", 'x'}, // Latin lowercase letter W
        {"2p", 'y'}, // Latin lowercase letter Y
        {"2q", 'z'}, // Latin lowercase letter Z
        // Subsegment 3: Punctuation & Symbols B
        {"30", '*'}, // Asterisk
        {"31", '/'}, // Slash
        {"32", '|'}, // Vertical bar
        {"33", '\\'}, // Backslash
        {"34", '<'}, // Less-than sign
        {"35", '='}, // Equals sign
        {"36", '>'}, // Greater sign
        {"37", '\xd7'}, // Multiplication sign
        {"38", '\xf7'}, // Division sign
        {"39", '#'}, // Number sign
        {"3a", '$'}, // Dollar sign
        {"3b", '%'}, // Percent sign
        {"3c", '('}, // Left parenthesis
        {"3d", ')'}, // Right parenthesis
        {"3e", '['}, // Left square bracket
        {"3f", ']'}, // Right square bracket
        {"3g", '{'}, // Left curly bracket
        {"3h", '}'}, // Right curly bracket
        {"3i", '^'}, // Circumflex accent
        {"3j", '`'}, // Grave accent
        {"3k", '~'}, // Tilde
    };


} // namespace termite

#endif // TCE_H34