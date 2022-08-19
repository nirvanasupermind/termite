This document is used for planning and outlining Termite and it's features. Many of these features may not be implemented yet.

As a convention, "0b" prefix is used for binary numbers and "0t" prefix is used for ternary numbers.

# Sizes
- Trybble (ternary analogue to nybble): 3 trits
- Tryte (ternary analogue to byte): 6 trits
- Word: 18 trits
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
- 3^9 = 19683 1-tryte memory registers

# CPU register
- 18-trit general-purpose registers `r0` - `r26`
- 18-trit instruction register `ir` (`r27`)
- 18-trit program counter `pc` (`r28`)

# Instruction set architecture
- All CPU instructions have a fixed width of 1 word (18 trits)
- Instruction format:
  - Empty-type: opcode (3 trits), unused space (15 trits)
  - I-type: opcode (3 trits), immediate (6 trits), unused space (9 trits)
  - A-type: opcode (3 trits), address (9 trits), unused space (6 trits)
  - RR-type: opcode (3 trits), register A (3 trits), register B (3 trits)
  - RA-type: opcode (3 trits), register (3 trits), address (9 trits) 
  - IA-type: opcode (3 trits), immediate (6 trits), address (9 trits) 
  - AR-type: opcode (3 trits), address (9 trits), register (3 trits)
  - RRR-type: opcode (3 trits), register A (3 trits), register B (3 trits), register C (3 trits)

- Instruction set:
  - No operation (`nop`, Empty-type)
  - Load tryte (`lt`, RA-type)
  - Load tryte immediate (`lti`, IA-type)
  - Store (`st`, AR-type)
  - Branch without condition (`b`, A-type)
  - Branch if equal (`beq`, AR-type)
  - Branch if not equal (`bne`, AR-type)
  - Branch if less than (`blt`, AR-type)
  - Branch if greater than (`bgt`, AR-type)
  - Branch if less than or equal (`ble`, AR-type)
  - Branch if greater than or equal (`bge`, AR-type)
  - Compare (`cmp`, RRR-type)
  - Syscall (`sys`, I-type)
  - Add (`add`, RRR-type)
  - Subtract (`sub`, RRR-type)
  - Multiply (`mul`, RRR-type)
  - Unsigned multiply (`umul`, RRR-type)
  - Divide (`div`, RRR-type)
  - Unsigned divide (`udiv`, RRR-type)
  - Negate (`neg`, RR-type)
  - Tritwise AND (`and`, RRR-type)
  - Tritwise OR (`or`, RRR-type)
  - Tritwise XOR (`xor`, RRR-type)
  - Tritwise NOT (`not`, RRR-type)
  - Left-shift (`ls`, RRR-type)
  - Right-shift (`rs`, RRR-type)
- Syscall services:
  - `0`: Print decimal value
  - `1`: Print ternary value
  - `2`: Print heptavigesimal value
  - `3`: Print TCE character
  - `4`: Read decimal value
  - `5`: Read ternary value
  - `6`: Read heptavigesimal value
  - `7`: Read TCE character
  - `8`: Exit (terminates with value)

- Example assembly program to add two numbers:
```
main:
  lti 1,r0; loads 1 into r0
  lti 2,r1; loads 1 into r0
  add r2,r0,r1; adds r0 and r1, storing result in r2
  sys $00,r2; prints r2
  sys $08,$00; exits with status code 0
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