# Number representation

# Processor architecture

## Memory
The 12-trit word size enables access to 531,441 words of memory. 

## CPU registers
The CPU contains 27 general-purpose 12-trit registers (`r0` to `r26`). `r25` is the stack pointer (`sp`), and `r26` is the program counter (`pc`).

## Addressing modes
The following addressing modes can be used for operands:

| Name               | Example       | Description                                  |
| ------------------ | ------------- | -------------------------------------------- |
| Immediate          | `#x`          | `x` is the operand                           |
| Absolute           | `x`           | `x` is the address of the operand            | 
| Register           | `rx`          | `rx` contains the operand                    | 

## Status flags
The following 1-trit status flags are used:

| Name               | Symbol        | Description                                                 | States                                                     |
| ------------------ | ------------- | ----------------------------------------------------------- | ---------------------------------------------------------- |
| Sign flag          | `s`           | Reports the sign of the result of the previous operation    | `s == 0`: zero, `s == 1`: positive, `s == 2`: negative     |
| Overflow flag      | `v`           | Reports if an overflow occurred in the previous operation   | `v == 0`: no overflow, `v == 1`: overflow, `v == 2`: never |
| Carry flag         | `c`           | Reports if a carry was generated in the previous operation  | `c == 0`: no carry, `c == 1`: carry, `c == 2`:  never       |

## Instruction set
| Mnemonic | Operation                                                      | Operands |
| -------- | -------------------------------------------------------------  | -------  |
| `nop`    | No operation                                                   | 0        |
| `mov`    | Move: `dest <- src`                                            | 2        |
| `add`    | Add: `dest <- dest + src`                                      | 2        |
| `adc`    | Add with carry: `dest <- dest + src + c`                       | 2        |
| `sub`    | Subtract: `dest <- dest - src`                                 | 2        |
| `mul`    | Multiply: `dest <- dest * src`                                 | 2        |
| `div`    | Divide: `dest <- dest / src`                                   | 2        |
| `mod`    | Modulo: `dest <- dest % src`                                   | 2        |
| `and`    | Tritwise AND: `dest <- dest & src`                             | 2        |
| `or`     | Tritwise OR: `dest <- dest \| src`                             | 2        |
| `xor`    | Tritwise XOR: `dest <- dest ^ src`                             | 2        |
| `sl`     | Shift left: `dest <- dest >> src`                              | 2        |
| `sr`     | Shift right: `dest <- dest << src`                             | 2        |
| `cmp`    | Compare: `set-flags(dest - src)`                               | 2        |
| `jmp`    | Jump: `pc <- opr`                                              | 1        |
| `je`     | Jump if equal (`s == 0`)                                       | 1        |
| `jne`    | Jump if not equal (`s == 1 \| s == 2`)                         | 1        |
| `jl`     | Jump if less (`s == 2`)                                        | 1        |
| `jg`     | Jump if greater (`s == 1`)                                     | 1        |
| `jle`    | Jump if less than or equal (`s == 2 \| s == 0`)                | 1        |
| `jge`    | Jump if greater than or equal (`s == 1 \| s == 0`)             | 1        |
| `jc`     | Jump if carry (`c == 1`)                                       | 1        |
| `jnc`    | Jump if not carry (`c == 0`)                                   | 1        |
| `jsr`    | Jump to subrotuine: `sp <- sp - 1; mem[sp] <- pc; pc <- opr`   | 1        |
| `ret`    | Return from subroutine: `pc <- mem[sp]; sp <- sp + 1`          | 0        |
| `push`   | Push to stack: `sp <- sp - 1; mem[sp] <- opr`                  | 1        |
| `pop`    | Pop from stack: `mem[opr] <- mem[sp]; sp <- sp + 1`            | 1        |
| `hlt`    | Halt                                                           | 0        |


## Instruction format
Two-operand instructions have 6 combinations of addressing modes that can be used as operands, which are each encoded seperately as 6 distinct opcodes.

* Zero-operand instructions: `opc` (6)
* One-operand instructions: `opc` (6), `opr` (12)
* Two-operand instructions (absolute-absolute & absolute-immediate): `opc` (6), `dest` (12), `src` (12)
* Two-operand instructions (absolute-register): `opc` (6), `dest` (12), unused (3), `src` (3)
* Two-operand instructions (register-absolute & register-immediate): `opcode` (6), unused (3), `dest` (3), `src` (12)
* Two-operand instructions (register-register): `opc` (6), `dest` (3), `src` (3)

## Assembly format
```
label:
    opc opr1,opr2,opr3...; comment 
```