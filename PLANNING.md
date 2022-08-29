This document is used for planning and outlining Termite and it's features. Many of these features may not be implemented yet.

As a convention, "0b" prefix is used for binary numbers and "0t" prefix is used for ternary numbers.

# Sizes
- Trybble (ternary analogue to nybble): 3 trits
- Tryte (ternary analogue to byte): 6 trits
- Halfword: 12 trits (2 trytes)
- Word: 24 trits (4 trytes)


<!-- 
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
  which translates to approximately 18 decimal digits of precision. -->

# Displaying numbers
Integers and floating-point numbers may be input and displayed in three number systems:
- Ternary (base 3), with digits `012`
- Decimal (base 10), with digits `0123456789`
- Heptavigesimal/Hept (base 27), with digits `0123456789ABCDEFGHIJKLMNOPQ`

# Memory
- 3^18 = 387420489 1-tryte memory registers (387 MT of memory)

# CPU registers
- 24-trit always-0 register (`$r0`)
- 24-trit general-purpose registers (`$r1` - `$r23`)
- 24-trit syscall code register (`$r24`)
- 24-trit instruction register (`$r25`)
- 24-trit program counter (`$r26`)

# Instruction set architecture
- All CPU instructions have a fixed width of 1 word (24 trits)
- Instruction format:
  - R-type: opcode (6), register 1 (3), register 2 (3), register 3 (3), unused space (9)
  - I-type: opcode (6), register 1 (3), register 2 (3), immediate (12)
  - J-type: opcode (6), address (18)
- Instruction set:
  - `nop`: no operation (R-type)
  - `syscall`: system call using `$r24` as code (J-type)
  - `add`: add (R-type)
  - `sub`: subtract (R-type)
  - `addi`: add immediate (I-type)
  - `addu`: add unsigned (R-type)
  - `subu`: subtract unsigned (R-type)
  - `addiu`: add immediate unsigned (I-type)
  - `mul`: multiply (R-type)
  - `mulu`: multiply unsigned (R-type)
  - `div`: divide (R-type)
  - `divu`: divide unsigned (R-type)
  - `and`: tritwise AND (R-type)
  - `or`: tritwise OR (R-type)
  - `andi`: tritwise AND immediate (I-type)
  - `ori`: tritwise OR immediate (I-type)
  - `lui`: load upper immediate (I-type)
  - `lw`: load word (I-type)
  - `sw`: store word (I-type)
  - `b`: Branch unconditionally (J-type)
  - `beq`: Branch if equal (I-type)
  - `bne`: Branch if not equal (I-type)
  - `blt`: Branch if less than (I-type)
  - `bltu`: Branch if less than unsigned (I-type)
  - `bgt`: Branch if greater than (I-type)
  - `bgtu`: Branch if greater than unsigned (I-type)
  - `ble`: Branch if less than or equal (I-type)
  - `bleu`: Branch if less than or equal unsigned (I-type)
  - `bge`: Branch if greater than (I-type)
  - `bgeu`: Branch if greate than or equal unsigned (I-type)

- Syscall services:
  - `0`: Print decimal value
  - `1`: Print ternary value
  - `2`: Print heptavigesimal value
  - `3`: Print TCE character
  - `4`: Read decimal value
  - `5`: Read ternary value
  - `6`: Read heptavigesimal value
  - `7`: Read TCE character
  - `8`: Exit

Example assembly program to add two numbers:
```
main:
  lw 1, $r1;
  lw 2, $r2;
  add $r1, $r2, $r3;
  lw 0, $r24;
  syscall $r3;
  lw 8, $r24;
  syscall;
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