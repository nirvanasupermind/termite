This document is used for planning and outlining Termite and it's features. Many of these features may not be implemented yet.

As a convention, "0b" prefix is used for binary numbers and "0t" prefix is used for ternary numbers.

# Sizes
- Commonly-used sizes for data types and instructions are 3, 6, 12, 24, etc. trits (powers of 2 times 3).

- A trybble (ternary analogue to nybble) is 3 trits.
- A tryte (ternary analogue to byte) is 2 trybbles, or 6 trits.

# Integer representation
- Unbalanced ternary system with digits {0, 1, 2} is used to store integers.
- Internally, each trit is stored as a pair of bits in "binary-coded ternary" format, with 0 = 0b00, 1 = 0b01, and 2 = 0b10.
- Signed integers use "3's complement" system to store negative integers, analogous to 2's complement.
  The "3's complement" of a number is made by subtracting it from 0t222...222 (the number of digits depends on the integer size), then adding 1.  
  For example, assuming an integer size of 3 trits, the 3's complement of 0t111 is 0t222 - 0t111 + 0t001 = 0t112.

# Floating-point representation
- Floating-point numbers are stored as two integers, the significand and exponent. The value of the floating-point number is significand*3^exponent.
- 24-trit (single-precision) floating-point numbers will use a 6-trit exponent and 18-trit significand, 
  which translates to approximately 8 decimal digits of precision.
- 48-trit (double-precision) floating-point numbers will use an 12-trit exponent and 36-trit significand, 
  which translates to approximately 18 decimal digits of precision.

# Displaying numbers
Integers and floating-point numbers may be input and displayed in three number systems:
- Ternary (base3) system with digits 0-2. Marked by the prefix `%` in assembly and `0t` in C-like language.
- Decimal (base10) system with digits 0-9. Default in both assembly and C-like language.
- Heptavigesimal/Hept (base27) system with digits 0-26, with digits 10-26 written as the letters a-q. 
  Marked by the prefix `$` in assembly and `0v` in C-like language.

# Random-access memory
- The random-access memory consists of 3^12 = 531441 memory registers, each of which holds 1 tryte and is uniquely addressed by 2 trytes.

# CPU registers
- 1-tryte general purpose registers `reg0` - `reg9`
- 1-tryte accumulator (`reg10`)
- 1-tryte program counter (`reg11`)

# Instruction set architecture
- A CPU instruction contains an opcode, addressing modes for the two operands, and the two operands themselves.
- All CPU instructions have a fixed width of 30 trits.
- Each instruction is represented in ternary as:
  `<4-trit opcode><1-trit addressing mode for operand #1><1-trit addressing mode for operand #2><12-trit operand #1><12-trit operand #2>`
- Each instruction is represented in assembly as:
  `<operation name> <addressing mode symbol for operand #1><literal for operand #1>,<addressing mode symbol for operand #2><literal for operand #2>;`

  For example:
  `mov #5,$6q;`
- Addressing modes:
  - Register-indirect addressing mode, with prefix `reg`, where interpreted value is the value located at the register following the addressing mode
  - Direct addressing mode (default), where interpreted value is the value located at the address following the addressing mode in RAM
  - Immediate addressing mode, with prefix `#`, where interpreted value is the address following the addressing mode
- Instruction set:
  - `nop`: No operation
  - `ret`: Return/exit
  - `mov`: Moves a value into an address
  - `syscall`: Does I/O operations with a specific mode passed as an operand
    - `syscall 0`: Inputs a decimal value and stores it in the accumulator
    - `syscall 1`: Inputs a ternary value and stores it in the accumulator
    - `syscall 2`: Inputs a hept value and stores it in the accumulator
    - `syscall 3`: Inputs a character and stores it's TCE code in the accumulator
    - `syscall 4`: Outputs the accumulator as a decimal value
    - `syscall 5`: Outputs the accumulator as a ternary value
    - `syscall 6`: Outputs the accumulator as a hept value
    - `syscall 7`: Outputs the accumulator as the character with the corresponding TCE code
  - `neg`: Adds two values and stores the result in the accumulator
  - `add`: Adds two values and stores the result in the accumulator
  - `sub`: Subtradcts two values and stores the result in the accumulator
  - `mul`: Multiplies two values and stores the result in the accumulator
  - `not`: Takes trit-wise NOT of a value and stores the result in the accumulator
  - `and`: Takes trit-wise AND of two values and stores the result in the accumulator
  - `or`: Takes trit-wise OR of two values and stores the result in the accumulator
  - `xor`: Takes trit-wise XOR of two values and stores the result in the accumulator
  - `cmp`: Compares two values and stores an indicator of -1, 0, or 1 in the accumulator
  - `jmp`: Jumps to a specific line or label
  - `je`: Jumps to a specific line or label if the accumulator is 0 (equality indicator)
  - `jne`: Jumps to a specific line or label if the accumulator is not 0 (equality indicator)
  - `jl`: Jumps to a specific line or label if the accumulator is -1 (less than indicator)x
  - `jg`: Jumps to a specific line or label if the accumulator is 1 (greater than indicator)  
  - `jle`: Jumps to a specific line or label if the accumulator is -1 (less than indicator) or 0 (equality indicator)
  - `jge`: Jumps to a specific line or label if the accumulator is 1 (greater than indicator) or 0 (equality indicator)

# Termite Character Encoding (TCE)
  - 1 tryte per character, and 3^6 = 729 characters
  - Divided into 3 segments, and 27 subsegments, with each subsegment corresponding to a hept digit
  - 3 segments will be Latin, Greek & Coptic, and Cyrillic(??)
  - 27 subsegments will be:
    - Subsegment `0`: Punctuation and Numbers
    - Subsegment `1`: Latin Uppercase
    - Subsegment `2`: Latin Lowercase
    - Subsegment `3`: Common Symbols 
    - Subsegment `4`: Latin Extension Uppercase 1
    - Subsegment `5`: Latin Extension Uppercase 2
    - Subsegment `6`: Latin Extension Lowercase 1
    - Subsegment `7`: Latin Extension Lowercase 2
    - Subsegment `8`: IPA Extensions
    - Subsegment `9`: Greek Uppercase
    - Subsegment `a`: Greek Lowercase