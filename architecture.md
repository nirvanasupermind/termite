Termite's instruction set architecture is a RISC architecture based entirely on balanced ternary.

Note that "tryte" is used here to refer to an 8-trit data type and "word" is used to refer to a 16-trit data type. Trits in a tryte or word are indexed from least to most significant, so trit 0 is the least signifcant trit.

All instructions are 16 trits or one word long, and there is a 16-trit address space of up to 3^16 (43046721) trytes of memory. Each memory address points to a tryte, and words are stored in memory as two trytes in little-endian order.

## Registers
There are 27 general purpose 16-trit registers numbered as `r-13` to `r13`.  `r12` is also referred to as `sp`, the stack pointer, initiallized to (3^16-1)/2 - 1 (21523360) and going downwards. `r13` is also referred to as `pc`, the program counter,  starting at -(3^16-1)/2 (-21523360).  There is also the special-purpose program status register `psr` for holding status flags.
## Flags
There are two status flags held in the program status register. The zeroth trit is the sign flag (`SF`), which is set to the sign of the result (-1, 0, or 1) after any arithmetic, tritwise, or compare instruction. The first trit is the carry flag (`CF`) which is set to the carry after an addition, subtraction, or compare instruction.
## Instruction listing
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
|`T01T`           |`not`   |Tritwise NOT                          |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = ~rs`                            |
|`T010`           |`noti`  |Tritwise NOT immediate                |opcode [15:12], `rd` [11:9], `imm` [8:6]               |`rd = ~imm`                           |
|`T011`           |`and`   |Tritwise AND                          |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs & rt`                        |
|`T1TT`           |`andi`  |Tritwise AND immediate                |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs & imm`                       |
|`T1T0`           |`or`    |Tritwise OR                           |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs \| rt`                       |
|`T1T1`           |`ori`   |Tritwise OR immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs \| imm`                      |
|`T10T`           |`lsh`   |Left shift                            |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs << rt`                       |
|`T100`           |`lshi`  |Left shift immediate                  |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs << imm`                      |
|`T101`           |`rsh`   |Right shift                           |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs >> rt`                       |
|`T11T`           |`rshi`  |Right shift immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs >> imm`                      |
|`T110`           |`cmp`   |Compare                               |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`SF = sign(rd - rs)`                  |
|`T111`           |`jmp`   |Uncoditional jump                     |opcode [15:12], `imm` [11:0]                           |`pc = imm`                            |
|`0TTT`           |`jeq`   |Jump if equal                         |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF == 0`               |
|`0TT0`           |`jne`   |Jump if not equal                     |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF != 0`               |
|`0TT1`           |`jlt`   |Jump if less than                     |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF < 0`                |
|`0T0T`           |`jle`   |Jump if less than or equal            |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF <= 0`               |
|`0T00`           |`jgt`   |Jump if greater than                  |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF > 0`                |
|`0T01`           |`jge`   |Jump if greater than or equal         |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `SF >= 0`               |
|`0T1T`           |`push`  |Push to stack                         |opcode [15:12], `imm` [11:0]                           |`sp = sp - 2; mem[sp] = imm`          |
|`0T10`           |`pop`   |Pop from stack                        |opcode [15:12], `rd` [11:9]                            |`rd = mem[sp]; sp = sp + 2`           |
|`0T11`           |`call`  |Call subroutine                       |opcode [15:12], `imm` [11:0]                           |`sp = sp - 2; mem[sp] = pc; pc = imm;`|
|`00TT`           |`ret`   |Return from subroutine                |opcode [15:12]                                         |`pc = mem[sp]; sp = sp + 2`           |
|`00T0`           |`sys`   |Syhstem call                          |opcode [15:12], `imm` [11:0]                           |                                      |

# System calls
|Code in `imm`    |Description                          |Operands       |         
|-----------------|-------------------------------------|---------------|
|0                |Print `r-13` as decimal number       |`r-13`         |
|1                |Print `r-13` as ternary number       |`r-13`         |
|2                |Print `r-13` as character            |`r-13`         |

00T1 0000 0000 0000
01 01 00 10