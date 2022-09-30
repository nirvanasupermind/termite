uWIP
# Number representation

## Floating-point numbers

# Processor architecture

## Memory
The 18-trit word size enables access to 531,441 words of memory. 

## CPU registers
The CPU contains 27 general-purpose 18-trit registers (`r0` to `r26`). `r25` is the stack pointer (`sp`), and `r26` is the program counter (`pc`). 

## Instruction formats
* R-type: `op` (4), `rs` (4), `rd` (4)
* I-type: `op` (4), `imm` (4), `rd` (4)
* J-type: `op` (4), `addr` (8)

## Instruction set
| Opcode | Mnemonic | Operation                                                  | Format |
| ------ | -------- | ---------------------------------------------------------- | ------ |
| `$00`  | `add`    | Add: `rd <- rs + rt`                                       | R-type |
| `$01`  | `addi`   | Add immediate: `rd <- rs + imm`                            | I-type |
| `$02`  | `sub`    | Subtract: `rd <- rs - rt`                                  | R-type |
| `$03`  | `mul`    | Multiply: `rd <- rs * rt`                                  | R-type |
| `$04`  | `mulu`   | Multiply unsigned: `rd <- rs * rt`                         | R-type |
| `$05`  | `div`    | Divide: `rd <- rs / rt`                                    | R-type |
| `$06`  | `divu`   | Divide unsigned: `rd <- rs / rt`                           | R-type |
| `$07`  | `mod`    | Modulo: `rd <- rs % rt`                                    | R-type |
| `$08`  | `modu`   | Modulo unsigned: `rd <- rs % rt`                           | R-type |
| `$09`  | `and`    | Tritwise AND: `rd <- rs & rt`                              | R-type |
| `$0A`  | `or`     | Tritwise OR: `rd <- rs \| rt`                              | R-type |
| `$0B`  | `xor`    | Tritwise OR: `rd <- rs ^ rt`                               | R-type |
| `$0C`  | `sl`     | Shift left: `rd <- rs >> shamt`                            | R-type |
| `$0D`  | `sr`     | Shift right: `rd <- rs << shamt`                           | R-type |
| `$0E`  | `sru`    | Shift right unsigned: `rd <- rs << shamt`                  | R-type |