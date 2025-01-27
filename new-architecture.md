# Mathematics
The balanced ternary (base 3) system uses 3 digits, -1, 0 and 1. Typically, -1 is assigned to `false`, 0 to `unknown`, and 1 to `true`. Since it is inconvenient to write -1 as a digit, the letter A is used for this purpose in Termite. Each position in a balanced ternary number represents a power of 3. For example, `10A1` in balanced ternary represents 1\*3^3 + 0\*3^2  + (-1)\*3^1 + 1\*3^0, which is 25 in decimal. The balanced ternary system can also represent negative numbers without a separate minus sign–for example, `A1A` is (-1)\*3^2 + 1\*3^1 + (-1)\*3^0, or -7 in decimal.

The balanced nonary (base 9) system uses 9 digits, -4, -3, -2, -1, 0, 1, 2, 3, and 4. The negative digits -4, -3, -2, and -1 are represented as D, C, B, and A in Termite. Balanced nonary may be used as a way to shorten balanced ternary in the same way hexadecimal is used to shorten binary, because each balanced nonary digit corresponds to a pair of balanced ternary digits:
```
D = AA
C = A0
B = A1
A = 0A
0 = 00
1 = 01
2 = 1A
3 = 10
4 = 11
```

For example, `10A1` in balanced ternary is `3B` in balanced nonary.


# Memory
## Data formats
The smallest unit of memory is 8 trits, which is referred to as a "tryte". Each word is 16 trits or 2 trytes. 16-trit words are stored in little-endian format, with the least significant tryte placed at the lower memory address. 

There is a 16-trit address system which allows access to 3^16 (43,046,721) trytes of memory.

# CPU registers
AX, BX, CX, DX, DI, SI, BP, SP

# Addressing modes
There are 5 addressing modes supported. The addressing mode takes up 2 trits.
|Trit|Addressing mode                         |Example    |
|----|----------------------------------------|-----------|
|`TT` |Register (value is in the register)|`ax`       |
|`T0` |Immediate (value is a constant) |`1`        |
|`T1` |Register indirect (value is at the memory address specified by the register) |`[ax]`        |
|`0T` |Direct (value is at the memory address specified by the constant) |`[1]`        |
|`00` |Indexed (value is at the memory address specified at the memory address specified by the register displaced by a constant) |`1[ax]`        |



# Instruction set
|Opcode (ternary) |Mnemonic|Instruction                           |Action                                |
|-----------------|--------|--------------------------------------|--------------------------------------|
|`TTTT`           |`mov`   |Move                                  |`Des <- Src`                          |
