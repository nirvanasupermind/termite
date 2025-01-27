# Mathematical background
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
`AX`, `BX`, `CX`, `DX,` `DI`, `SI`, `BP`, `SP`, `FLAGS`

# Addressing modes
There are 3 addressing modes supported. The addressing mode takes up 1 trit in the instruction format.

|Trit|Addressing mode    |Example    |Description|
|----|-------------------|-----------|-----------|
|`A` |Immediate          |`1`        |The operand is the next word of the instruction|
|`0` |Register           |`ax`       |The operand is in the register|
|`1` |Indexed            |`1[ax]`    |The operand's address is the value of the register plus the next word of the instruction|

# Instruction set
Note: In the "Action" column, `[n]` refers to the value located at address n

Note 2: Logical/shift operations do not work the same way as normal, because they operate on ternary and three-valued logic. a << b = a * 3^b instead of a * 2^b

|Opcode (nonary)|Mnemonic|Description                       |Operands                              |Action                              |
|---------------|--------|----------------------------------|--------------------------------------|------------------------------------|
|`DD`           |`mov`   |Move                              |`dest` (reg/idx), `src `(imm/reg/idx) |`dest = src`                        |
|`DC`           |`push`  |Push word onto stack              |`src` (imm/reg/idx)                   |`sp = sp - 2; [sp] = src`           |
|`DB`           |`pop`   |Pop word off stack and store it   |`dest` (reg/idx)                      |`dest = [sp]; sp = sp + 2`          |
|`DA`           |`and`   |Trit-wise logical AND             |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest & src`                 |
|`D0`           |`or`    |Trit-wise logical OR              |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest \| src`                |
|`D1`           |`xor`   |Trit-wise logical XOR             |`dest` (reg/idx), `src` (reg/idx)     |`dest = dest ^ src`                 |
|`D2`           |`shl`   |Shift left                        |`dest` (reg/idx), `src` (reg/idx)     |`dest = dest << src`                |
|`D3`           |`shr`   |Shift right                       |`dest` (reg/idx), `src` (reg/idx)     |`dest = dest >> src`                |
