This document is used for planning and outlining Termite and it's features. Many of these features may not be implemented yet.

As a convention, "0b" prefix is used for binary numbers and "0t" prefix is used for ternary numbers.

# Sizes
- Commonly-used sizes for data types and instructions are 3, 6, 12, 24, 48, etc. trits (3 times the powers of 2).

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
- 60-trit (extended-precision) floating-point numbers will use a 24-trit exponent and 36-trit significand, 
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
- 1-tryte general purpose registers `r0` - `r11`
- 2-tryte program counter `pc`

# Instruction set architecture
- All CPU instructions have a fixed width of 24 trits or 4 trytes.
- Each instruction is represented in ternary as:
  `<6-trit opcode><6-trit register #1><6-trit register #2><6-trit unused space>`
  or `<6-trit opcode><6-trit register #1><6-trit value><6-trit unused space>`
  or `<6-trit opcode><6-trit register #1><12-trit address>`

- Instruction set:
  - `nop;` (`$00`): No operation
  - `exit <code>;` (`$01`): Exits with status code `<code>`
  - `load <addr>,<reg>;` (`$02`): Loads the value located at the memory address `<addr>` into register `<reg>`
  - `loadi <val>,<reg>;` (`$03`): Loads `<val>` into register `<reg>`
  - `store <reg>,<addr>;` (`$04`): Stores the value located at register `<reg>` into the memory address `<addr>`
  - `storei <val>,<addr>;` (`$05`): Stores `<val>` into the memory address `<addr>`
  - `neg <reg>;` (`$06`): Negates the value located at register `<reg>`, storing the result in `<reg>`
  - `add <reg1>,<reg2>;` (`$07`): Adds the values located at registers `<reg1>` and `<reg2>`, storing the result in `<reg2>`
  - `addi <val>,<reg2>;` (`$08`): Adds `<val>` to the value located at register `<reg2>`, storing the result in `<reg2>`
  - `sub <reg1>,<reg2>;` (`$09`): Subtracts the values located at registers `<reg1>` and `<reg2>`, storing the result in `<reg2>`
  - `subi <val>,<reg2>;` (`$0A`): Subtracts `<val>` from the value located at register `<reg2>`, storing the result in `<reg2>`
  - `mul <reg1>,<reg2>;` (`$0B`): Multiplies the values located at registers `<reg1>` and `<reg2>`, storing the result in `<reg2>`
  - `muli <val>,<reg2>;` (`$0C`): Multiplies `<val>` by the value located at register `<reg2>`, storing the result in `<reg2>`


# Termite Character Encoding (TCE)
  - 1 tryte per character, and 3^6 = 729 characters
  - Divided into 3 segments, and 27 subsegments, with each subsegment corresponding to a hept digit


# C-like language example
```
int12 fac(int12 a) {
  if(a == 0) {
    return 1;
  } else {
    return a * fac(a - 1);
  }
}

void main() {
  print("{1}\n", fac(5)); // 120
}

```