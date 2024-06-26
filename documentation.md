# Table of contents
* [1 Ternary mathematics and logic](#1-ternary-mathematics-and-logic)
    * [1.1 Balanced ternary](#11-balanced-ternary)
    * [1.2 Binary-coded ternary](#12-binary-coded-ternary)
    * [1.3 Ternary logic](#13-ternary-logic)
* [2 Termite architecture](#2-termite-architecture)
    * [2.1 Registers](#21-registers)
    * [2.2 Flags](#22-flags)
    * [2.3 Instruction listing](#23-instruction-listing)
    * [2.4 Characters](#24-characters)
    * [2.5 Assembly format](#25-assembly-format)


# 1 Ternary mathematics and logic
## 1.1 Balanced ternary 
The balanced ternary (base 3) system uses 3 digits, -1, 0 and 1, in contrast to the more common binary (base 2) system used by the vast majority of computers, and the everyday decimal (base 10) system. Typically, -1 is assigned to `false`, 0 to `unknown`, and 1 to `true`. Since it is inconvenient to write -1 as a digit, the letter T is used for this purpose in Termite. Each position in a balanced ternary number represents a power of 3. For example, `10T1` in balanced ternary represents 1\*3^3 + 0\*3^2  + (-1)\*3^1 + 1\*3^0, which is 25 in decimal. The balanced ternary system can also represent negative numbers without a separate minus sign–for example, `T1T` is (-1)\*3^2 + 1\*3^1 + (-1)\*3^0, or -7 in decimal.

## 1.2 Binary-coded ternary 
Termite is an emulator, so it requires storage of ternary data on a binary computer. To accomplish, Termite internally uses a system known as [binary-coded ternary](https://en.3wikipedia.org/wiki/Ternary_numeral_system#Binary-coded_ternary) (BCT) where each trit is mapped to two bits. Binary-coded ternary encodings vary, especially for balanced ternary, but in Termite the encoding used is to map the balanced ternary digit -1 to the bits `00`, 0 to `01` and 1 to `10`.

## 1.3 Ternary logic
Analogous to Boolean logic for the binary system, a logic system can be built on balanced ternary.  A ternary logic uses 3 truth values indicating true, false, and a third "unknown" or "both" state. `false`, `unknown` and `true` are usually mapped to the balanced ternary digits -1, 0, and 1 respectively. Some ternary logic systems, such as Kleene's "strong logic of indeterminacy", can extend standard Boolean operators to encompass this third state. In Kleene logic, the logical operators are defined as follows:

|`~a`     |         |
|---------|---------|
|`false`  |`true`   |
|`unknown`|`unknown`|
|`true`   |`false`  |

|`a & b`  |`false`  |`unknown`|`true`   |
|---------|---------|---------|---------|
|`unknown`|`false`  |`unknown`|`unknown`|
|`true`   |`false`  |`unknown`|`true`   |

|`a \| b` |`false`  |`unknown`|`true`   |
|---------|---------|---------|---------|
|`false`  |`false`  |`unknown`|`true`   |
|`unknown`|`unknown`|`unknown`|`true`   |
|`true`   |`true`   |`true`   |`true`   |

There is no XOR operator in Kleene logic, but it is defined in Termite as the sum of the arguments modulo 3 (if `false`, `unknown` and `true` are treated as -1, 0, and 1), analogous to how the boolean XOR is the sum of the arguments modulo 2:

|`a ^ b`  |`false`  |`unknown`|`true`   |
|---------|---------|---------|---------|
|`false`  |`true`   |`false`  |`unknown`|
|`unknown`|`false`  |`unknown`|`true`   |
|`true`   |`unknown`|`true`   |`false`  |

Note that, unlike the case with AND and OR, this operation e
# 2 Termite architecture
Termite's instruction set architecture is a RISC architecture based entirely on balanced ternary.

Note that "tryte" is used here to refer to an 8-trit data type and "word" is used to refer to a 16-trit data type. Trits in a tryte or word are indexed from least to most significant, so trit 0 is the least signifcant trit.

All instructions are 16 trits or one word long, and there is a 16-trit address space of up to 3^16 (43046721) trytes of memory. Each memory address points to a tryte, and words are stored in memory as two trytes in little-endian order.

## 2.1 Registers
There are 27 general purpose 16-trit registers numbered as `r-13` to `r13`.  `r12` is also referred to as `sp`, the stack pointer, initiallized to (3^16-1)/2 - 1 (21523360) and going downwards. `r13` is also referred to as `pc`, the program counter,  starting at -(3^16-1)/2 = -21523360.  There is also the special-purpose program status register `psr` for holding status flags.
## 2.2 Flags
There are two status flags held in the program status register. The zeroth trit is the sign flag (`SF`), which is set to the sign of the result (-1, 0, or 1) after any arithmetic, tritwise, or compare instruction. The first trit is the carry flag (`CF`) which is set to the carry after an addition, subtraction, or compare instruction.
## 2.3 Instruction listing
|Opcode (ternary) |Mnemonic|Description                           |Format                                                 |Action                                |
|-----------------|--------|--------------------------------------|-------------------------------------------------------|--------------------------------------|
|`TTTT`           |`mov`   |Move                                  |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs`                             |           
|`TTT0`           |`movi`  |Move immediate                        |opcode [15:12], `rd` [11:9], `imm` [8:0]               |`rd = imm`                            |
|`TTT1`           |`movps` |Move program status register          |opcode [15:12], `rd` [11:9]                            |`rd = psr`                            | 
|`TT0T`           |`ld`    |Load                                  |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = mem[rs + imm]`                  |
|`TT00`           |`st`    |Store                                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`mem[rs + imm] = rd`                  |
|`TT01`           |`add`   |Add                                   |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs + rt`                        |
|`TT1T`           |`addi`  |Add immediate                         |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + imm`                       |
|`TT10`           |`addc`  |Add with carry                        |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + rt + CF`                   |
|`TT11`           |`addci` |Add with carry immediate              |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + imm + CF`                  |
|`T0TT`           |`sub`   |Subtract                              |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs - rt`                        |
|`T0T0`           |`subi`  |Subtract immediate                    |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs - imm`                       |
|`T0T1`           |`subc`  |Subtract with carry                   |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs - rt - CF`                   |
|`T00T`           |`subci` |Subtract with carry immediate         |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs - imm - CF`                  |
|`T000`           |`mul`   |Multiply                              |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs * rt`                        |
|`T001`           |`muli`  |Multiply immediate                    |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs * imm`                       |
|`T01T`           |`div`   |Divide                                |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs / rt` (adjacent register to `rd` = `rs % rt`)|
|`T010`           |`divi`  |Divide immediate                      |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs / imm` (adjacent register to `rd` = `rs % imm`)|
|`T011`           |`not`   |Tritwise NOT                          |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = ~rs`                            |
|`T1TT`           |`noti`  |Tritwise NOT immediate                |opcode [15:12], `rd` [11:9], `imm` [8:0]               |`rd = ~imm`                           |
|`T1T0`           |`and`   |Tritwise AND                          |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs & rt`                        |
|`T1T1`           |`andi`  |Tritwise AND immediate                |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs & imm`                       |
|`T10T`           |`or`    |Tritwise OR                           |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs \| rt`                       |
|`T100`           |`ori`   |Tritwise OR immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs \| imm`                      |
|`T101`           |`xor`   |Tritwise XOR                          |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs ^ rt`                        |
|`T11T`           |`xori`  |Tritwise XOR immediate                |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs ^ imm`                       |
|`T110`           |`lsh`   |Left shift                            |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs << rt`                       |
|`T111`           |`lshi`  |Left shift immediate                  |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs << imm`                      |
|`0TTT`           |`rsh`   |Right shift                           |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs >> rt`                       |
|`0TT0`           |`rshi`  |Right shift immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs >> imm`                      |
|`0TT1`           |`cmp`   |Compare                               |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`SF = sign(rd - rs)`                  |
|`0T0T`           |`cmpi`  |Compare immediate                     |opcode [15:12], `rd` [11:9], `imm` [8:0]               |`SF = sign(rd - imm)`                 |
|`0T00`           |`b`     |Uncoditional branch                   |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm`                       |
|`0T01`           |`beq`   |Branch if equal                       |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF == 0`          |
|`0T1T`           |`bne`   |Branch if not equal                   |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF != 0`          |
|`0T10`           |`blt`   |Branch if less than                   |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF < 0`           |
|`0T11`           |`ble`   |Branch if less than or equal          |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF <= 0`          |
|`00TT`           |`bgt`   |Branch if greater than                |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF > 0`           |
|`00T0`           |`bge`   |Branch if greater than or equal       |opcode [15:12], `imm` [11:0]                           |`pc = pc + imm` if `SF >= 0`          |
|`00T1`           |`push`  |Push to stack                         |opcode [15:12], `imm` [11:0]                           |`sp = sp - 2; mem[sp] = imm`          |
|`000T`           |`pop`   |Pop from stack                        |opcode [15:12], `rd` [11:9]                            |`rd = mem[sp]; sp = sp + 2`           |
|`0000`           |`call`  |Call subroutine                       |opcode [15:12], `imm` [11:0]                           |`sp = sp - 2; mem[sp] = pc; pc = pc + imm;`|
|`0001`           |`ret`   |Return from subroutine                |opcode [15:12]                                         |`pc = mem[sp]; sp = sp + 2`           |
|`001T`           |`sys`   |System call                           |opcode [15:12], `imm` [11:0]                           |                                      |

## System calls
|Code in `imm`    |Description                                 |Operands       |         
|-----------------|--------------------------------------------|---------------|
|0                |Exit program                                |               |
|1                |Print `r-13` as decimal number              |`r-13`         |
|2                |Print `r-13` as ternary number              |`r-13`         |
|3                |Print `r-13`'s low tryte as character       |`r-13`         |
|4                |Print `r-13`'s high tryte as character      |`r-13`         |
|5                |Input decimal number into `r-13`            |               |
|6                |Input ternary number into `r-13`            |               |
|7                |Input character into `r-13`'s low tryte     |               |
|8                |Input character into `r-13`'s high tryte    |               |
|9                |Print all registers (like in verbose mode)  |               |

## 2.4 Characters
Characters use a fixed-width encoding with each as 1 tryte. The numbers 0 through 3280 (ternary `11111111`), the maximum positive value of a tryte, represent the first 3280 characters of Unicode from `U+0000` to `U+0CD0`. (This is temporary, a custom character encoding organized by powers of 3 will most likely be added in the future.)

## 2.5 Assembly format
In the Termite assembly language, instructions are written as

```
label:
    <instr name> <arg 1>, <arg 2>, ...; # comment
    <instr name> <arg 1>, <arg 2>, ...; # comment
    ...
```

Instructions are separated by semicolons. All labels are followed by a colon, and comments, if present, are preceded by a pound sign. Balanced ternary numbers can be written with a C-style prefix `0r` (derived from the R in ternary, since T is the digit for -1), for example `0r1T` is 2. Both uppercase and lowercase T for -1 are accepted.