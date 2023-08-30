Termite's instruction set architecture is loosely based on RISC architectures, mainly early versions of ARM, but entirely based on balanced ternary.

Note that "tryte" is used here to refer to an 8-trit data type and "word" is used to refer to a 16-trit data type. (This was chosen because these can be efficiently have their binary-coded ternary data stored in `uint16_t` and `uint32_t`)

Each instruction is 16 trits, and there is a 16-bit address space of up to 43046721 trytes of memory.

# Registers
There are 9 general purpose 16-trit registers numbered as `r-4` to `r4`. All registers are orthogonal with no specific designated purpose, except for `r3` and `r4` which have the aliases `lr` and `pc` and function as the link register and program counter respectively.

# Instruction listing
Instruction formats are numbered here due to many of them being the same.

|Opcode (ternary) |Mnemonic|Description|Format |Action              |
|-----------------|--------|-----------|-------|--------------------|
|`TTTT`           |`mov`   |Move       |1      |`rm = `             |

Format 1:
|---|
|--