Termite's instruction set architecture is based on small RISC architectures, in particular the earliest 26-bit versions of ARM, but entirely based on balanced ternary.

Note that "tryte" is used here to refer to an 8-trit data type and "word" is used to refer to a 16-trit data type. (This was chosen because these can be efficiently have their binary-coded ternary data stored in `uint16_t` and `uint32_t`)

All instructions are 16 trits or 1 word long, and there is a 16-bit address space of up to 43046721 trytes of memory.

## Registers
There are 9 general purpose 16-trit registers numbered as `r-4` to `r4`. All registers are orthogonal with no specific designated purpose, except for `r3` and `r4` which have the aliases `lr` and `pc` and function as the link register and program counter respectively.

## Instruction listing
|Opcode (ternary) |Mnemonic|Description                           |Instruction format (see below)|Action                       |
|-----------------|--------|--------------------------------------|------------------------------|-----------------------------|
|`TTTT`           |`mov`   |Move                                  |1                             |`rd = rm`                    |
|`TTT0`           |`movi`  |Move immediate                        |2                             |`rd = imm`                   |
|`TTT1`           |`mvn`   |Move trit-wise NOT/negation           |1                             |`rd = ~rm`                   |
|`TTT1`           |`mvni`  |Move trit-wise NOT/negation immediate |2                             |`rd = ~imm`                  |
|`TTT1`           |`ldr`   |Load register                         |1                             |`rd = mem[rn + rm]`          |
|`TT0T`           |`ldri`  |Load register immediate               |2                             |`rd = mem[rn + imm]`         |
|`TT00`           |`str`   |Store register                        |1                             |`mem[rn + rm] = rd`          |
|`TT01`           |`stri`  |Store register immediate              |2                             |`mem[rn + imm] = rd`         |
|`TT01`           |`add`   |Store register immediate              |                              |`mem[rn + imm] = rd`         |
|`TT01`           |`add`   |Store register immediate              |                              |`mem[rn + imm] = rd`         |