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
- 1-tryte jump conditional `jc`
- 2-tryte program counter `pc`
- 4-tryte instruction register `ir`

# Instruction set architecture
- All CPU instructions have a fixed width of 24 trits or 4 trytes.
- Each instruction is represented in ternary as:
  `<6-trit opcode><6-trit register #1><6-trit register #2><6-trit register #3>`
  or `<6-trit opcode><6-trit register #1><12-trit address>`
  or `<6-trit opcode><6-trit interrupt status><6-trit register>`
- Instruction set:
  - `nop` (`$00`): No operation
  - `int <status>,<reg>;` (`$01`): Software interrupt
    - `int $00;`: Exits with successful signal
    - `int $01;`: Exits with unsuccessful signal 
    - `int $02,<reg>;`: Outputs register as decimal value
    - `int $03,<reg>;`:  Outputs register as ternary value
    - `int $04,<reg>;`:  Outputs register as heptavigesimal value
    - `int $05,<reg>;`:  Outputs register as TCE character
    - `int $06,<reg>;`:  Input decimal value into register
    - `int $07,<reg>;`:  Input ternary value into register
    - `int $08,<reg>;`:  Input heptavigesimal value into register
    - `int $09,<reg>;`:  Input TCE character into register
  - `ld <addr>;` (`$02`): Copy from memory to register
  - `ldv <val>;` (`$03`): Copy value to register
  - `st <reg>;` (`$04`): Copy from register to memory
  - `stv <val>;` (`$05`): Copy value to memory  
  - `add <regA>,<regB>,<regOut>;` (`$06`): Adds two registers
  - `sub <regA> <regB>,<regOut>;` (`$07`): Subtracts two registers
  - `mul <regA>,<regB>,<regOut>;` (`$08`): Multiplies two registers
  - `mulu <regA>,<regB>,<regOut>;` (`$09`): Multiplies two registers (unsigned)
  - `div <regA>,<regB>,<regOut>;` (`$0A`): Divides two registers
  - `divu <regA>,<regB>,<regOut>;` (`$0B`): Divides two registers (unsigned)
  - `not <reg>,<regOut>;` (`$0C`): Takes tritwise NOT of a register
  - `and <regA>,<regB>,<regOut>;` (`$0D`): Takes tritwise AND of two registers
  - `or <regA>,<regB>,<regOut>;` (`$0E`): Takes tritwise OR of two registers
  - `xor <regA>,<regB,<regOut>>;` (`$0F`): Takes tritwise XOR of two registers
  - `shl <regA>,<regB>,<regOut>;` (`$0G`): Takes left-shift of a register
  - `shr <regA>,<regB>,<regOut>;` (`$0H`): Takes right-shift of a register
  - `jmp <label>;` (`$0I`): Jumps to a label
  - `jeq <label>,<regA>,<regB>;` (`$0J`): Jumps if register A's value is equal to register B's
  - `jne <label>,<regA>,<regB>;` (`$0K`): Jumps if register A's value is not equal to register B's
  - `jlt <label>,<regA>,<regB>;` (`$0L`): Jumps if register A's value is less than register B's
  - `jgt <label>,<regA>,<regB>;` (`$0M`): Jumps if register A's value is greater than register B's
  - `jle <label>,<regA>,<regB>;` (`$0N`): Jumps if register A's value is less than or equal to register B's
  - `jge <label>,<regA>;` (`$0O`): Jumps if register A's value is greater than or equal to register B's

- Example assembly program to print all numbers from 1 to 10:
```
main:
  ldv 1,r0; loads 1 into r0
  add r0,r1,r2; adds r0 and r1, storing result in r2
  int $02,r2; prints r2
  ldv 10,r3; loads 10 into r3
  jle main,r0,r3; jumps back to start if r0 <= 10
  int $00; exits
```

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
  print("{0}\n", fac(5)); // 120
}
```