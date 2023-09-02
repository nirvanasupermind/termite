Termite's instruction set architecture is a RISC architecture based entirely on balanced ternary\.

Note that "tryte" is used here to refer to an 8-trit data type and "word" is used to refer to a 16-trit data type.

All instructions are 16 trits or one word long, and there is a 16-trit address space of up to 3^16 (43046721) trytes of memory. Each memory address points to a tryte, and words are stored in memory as two trytes in little-endian order.

## Registers
There are 27 general purpose 16-trit registers numbered as `r-13` to `r13`.  `r12` is also referred to as `sp`, the stack pointer, starting at 3^16-1 and goes downwards. `r13` is also referred to as `pc`, the program counter. All other registers do not have any designated purpose. 

## Instruction listing
|Opcode (ternary) |Mnemonic|Description                           |Format                                                 |Action                        |
|-----------------|--------|--------------------------------------|-------------------------------------------------------|------------------------------|
|`TTTT`           |`mov`   |Move                                  |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs`                     |              
|`TTT0`           |`movi`  |Move immediate                        |opcode [15:12], `rd` [11:9], `imm` [8:0]               |`rd = imm`                    |
|`TTT1`           |`ld`    |Load                                  |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = mem[rs + imm]`          |
|`TT0T`           |`st`    |Store                                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`mem[rs + imm] = rd`          |
|`TT00`           |`add`   |Add                                   |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs + rt`                |
|`TT01`           |`addi`  |Add immediate                         |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + imm`               |
|`TT1T`           |`addc`  |Add with carry                        |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + imm`               |
|`TT10`           |`addc`  |Add with carry immediate              |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs + imm`               |
|`TT11`           |`sub`   |Subtract                              |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs - rt`                |
|`T0TT`           |`subi`  |Subtract immediate                    |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs - imm`               |
|`T0T0`           |`subc`  |Subtract with carry                   |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs - rt - C`            |
|`T0T1`           |`subci` |Subtract with carry immediate         |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs - imm - C`           |
|`T00T`           |`mul`   |Multiply                              |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs * rt`                |
|`T000`           |`muli`  |Multiply immediate                    |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs * imm`               |
|`T001`           |`not`   |Tritwise NOT                          |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = ~rs`                    |
|`T01T`           |`noti`  |Tritwise NOT immediate                |opcode [15:12], `rd` [11:9], `imm` [8:6]               |`rd = ~imm`                   |
|`T010`           |`and`   |Tritwise AND                          |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs & rt`                |
|`T011`           |`andi`  |Tritwise AND immediate                |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs & imm`               |
|`T1TT`           |`or`    |Tritwise OR                           |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs | rt`                |
|`T1T0`           |`ori`   |Tritwise OR immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`rd = rs | imm`               |
|`T1T1`           |`lsh`   |Left shift                            |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs << rt`               |
|`T10T`           |`lshi`  |Left shift immediate                  |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs << imm`              |
|`T100`           |`rsh`   |Right shift                           |opcode [15:12], `rd` [11:9], `rs` [8:6], `rt` [5:3]    |`rd = rs >> rt`               |
|`T101`           |`rshi`  |Right shift immediate                 |opcode [15:12], `rd` [11:9], `rs` [8:6], `imm` [5:0]   |`rd = rs >> imm`              |
|`T11T`           |`cmp`   |Compare                               |opcode [15:12], `rd` [11:9], `rs` [8:6]                |`S = sign(rd - rs)`           |
|`T110`           |`jmp`   |Uncoditional jump                     |opcode [15:12], `imm` [11:0]                           |`pc = imm`                    |
|`T111`           |`jeq`   |Jump if equal                         |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S == 0`        |
|`0TTT`           |`jne`   |Jump if not equal                     |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S != 0`        |
|`0TT0`           |`jlt`   |Jump if less than                     |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S < 0`         |
|`0TT1`           |`jle`   |Jump if less than or equal            |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S <= 0`        |
|`0T0T`           |`jgt`   |Jump if greater than                  |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S > 0`         |
|`0T00`           |`jge`   |Jump if greater than or equal         |opcode [15:12], `imm` [11:0]                           |`pc = imm` if `S >= 0`        |
|`0T01`           |`call`  |Call subroutine                       |opcode [15:12], `imm` [11:0]                           |`pc = imm`                    |

## System calls
