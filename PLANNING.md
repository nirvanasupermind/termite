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
- Ternary (base 3), digits `012`
- Decimal (base 10), digits `0123456789`
- Heptavigesimal/Hept (base 27), digits `0123456789ABCDEFGHIJKLMNOPQ`

# Memory
- 3^10 = 59049 1-tryte memory registers

# CPU registers
- 1-tryte general-purpose registers `r0` - `r11`
- 2-tryte program counter `pc`
- 4-tryte instruction register `ir`

# Instruction set architecture
- All CPU instructions have a fixed width of 18 trits or 3 trytes
- Instruction format:
  - For `nop`: `<4-trit opcode><14-trit unused space>`
  - For arithmetic and logical instructions: `<4-trit opcode><4-trit register 1><4-trit register 2><4-trit destination><2-trit unused space>`
  - For `ld`: `<4-trit opcode><10-trit source><4-trit destination>`
  - For `ldv`: `<4-trit opcode><6-trit source><4-trit destination><4-trit unused space>`
  - For `st`: `<4-trit opcode><4-trit source><10-trit destination>` 

- Instruction set:
  - No operation (`nop`)
  - Add (`add REG, REG`)
  - Subtract (`sub REG, REG, REG`)
  - Multiply (`mul REG, REG, REG`)
  - Unsigned multiply (`umul REG, REG, REG`)
  - Divide (`div RRG, REG, REG`)
  - Unsigned divide (`udiv REG, REG, REG`)
  - Tritwise AND (`and REG, REG, REG`)
  - Tritwise OR (`or REG, REG, REG`)
  - Tritwise XOR (`xor REG, REG, REG`)
  - Load (`ld REG, REG, REG`)
  - Load value (`ldv`)
  - Store (`st`)
  - Syscall (`sys`)
- Syscall services: TBA

- Example assembly program to print all numbers from 1 to 10:
```
main:
  ldv 1,r0; loads 1 into r0
  add r0,r1,r2; adds r0 and r1, storing result in r2
  sys $00,r2; prints r2
  ldv 10,r3; loads 10 into r3
  ble main,r0,r3; goes back to start if r0 <= 10
  sys $08,0; exits successfully
  
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