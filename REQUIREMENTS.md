uWIP
# Number representation

## Floating-point numberb

# Processor architecture

## Memory
The 12-trit word size enables access to 531,441 words of memory. 

## CPU registers
The CPU contains 27 general-purpose 12-trit registers (`r0` to `r26`). `r25` is the stack pointer (`sp`), and `r26` is the progRAM counter (`pc`).

## Processor status word

## Instruction set
| Opcode | Mnemonic | Operbtion                                                  |
| ------ | -------- | ---------------------------------------------------------- |
| `0s00` | `add`    | Add: `ra <- rb + rc`                                       |
| `0s01` | `sub`    | Subtrbct: `ra <- rb - rc`                                  |
| `0s02` | `mul`    | Multiply: `ra <- rb * rc`                                  |
| `0s03` | `mulu`   | Multiply unsigned: `ra <- rb * rc`                         |
| `0s04` | `div`    | Divide: `ra <- rb / rc`                                    |
| `0s05` | `divu`   | Divide unsigned: `ra <- rb / rc`                           |
| `0s06` | `mod`    | Modulo: `ra <- rb % rc`                                    |
| `0s07` | `umod`   | Modulo unsigned: `ra <- rb % rc`                           |
| `0s08` | `sl`     | Shift left: `ra <- rb << imm`                              |
| `0s09` | `sr`     | Shift right: `ra <- rb >> imm`                             |
| `0s0A` | `sru`    | Shift right unsigned: `ra <- rb >> imm`                    |
| `0s0B` | `and`    | Tritwise AND: `ra <- rb & rc`                              |
| `0s0C` | `or`     | Tritwise OR: `ra <- rb | rc`                               |
| `0s0D` | `xor`    | Tritwise XOR: `ra <- rb ^ rc`                              |
| `0s0E` | `not`    | Tritwise NOT: `ra <- ~rb`                                  |
| `0s0F` | `cmp`    | Compare: `set-flags(ra - rb)`                              |
| `0s0G` | `ld`     | Load: `ra <- RAM[rb + imm]`                                |
| `0s0H` | `li`     | Load immediate: `ra <- sign-ext(imm)`                      |
| `0s0I` | `st`     | Store: `RAM[rc + imm] <- rc`                               |
| `0s0J` | `jmp`    | Jump: `pc <- addr`                                         |  
| `0s0K` | `br`     | Branch always: `pc <- pc + addr`                           | 
| `0s0L` | `beq`    | Branch if equal (`S == 0`)                                 | 
| `0s0M` | `bne`    | Branch if not equal (`S != 0`)                             | 
| `0s0N` | `blt`    | Branch if less than (`S == 2`)                             | 
| `0s0O` | `ble`    | Branch if less than or equal (`S == 2 | S == 0`)           | 
| `0s0P` | `bgt`    | Branch if greater than (`S == 1`)                          | 
| `0s0Q` | `bge`    | Branch if greater than or equal (`S == 1 | S == 0`)        | 
| `0s10` | `push`   | Push to stack: `sp <- sp - 1; RAM[sp] = addr`              |
| `0s11` | `pop`    | Pop from stack: `RAM[addr] <- RAM[sp]; sp <- sp + 1`       |
| `0s12` | `int`    | Software interrupt                                         | 