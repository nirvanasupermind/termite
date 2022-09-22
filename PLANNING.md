# Number representation
<!-- Termite uses 12-trit integers and 24-trit floating-point numbers. Since floating-point numbers take up 2 words of space, floating-point intructions use odd-numbered registers only  – for example, passing `r1` to a floating-point instruction will impliticly specify a floating-point number whose hi word is `r1` and lo word is `r2`. -->

# Processor architecture

## Memory
The 12-trit word size enables access to 531,441 words of memory.

## CPU registers
The CPU contains 27 general-purpose 12-trit registers (r0 to r26). r26 is the program counter (PC), and r25 is the stack pointer (SP).

             
## Instructions
| Mnemonic  |       Operands       |                Description              |  Opcode  |
| --------  | -------------------- | --------------------------------------- | -------- |
| `ADD`     | `rs`, `rd`           | Add                                     | `0nDD`   |
| `ADDC`    | `rs`, `rd`           | Add with carry                          | `0nDC`   |
| `SUB`     | `rs`, `rd`           | Subtract                                | `0nDB`   |
| `MUL`     | `rs`, `rd`           | Multiply                                | `0nDA`   |
| `DIV`     | `rs`, `rd`           | Divide                                  | `0nD0`   |
| `MOD`     | `rs`, `rd`           | Modulo                                  | `0nD1`   |
| `FADD`    | `rs`, `rd`           | Floating-point add                      | `0nD2`   |
| `FSUB`    | `rs`, `rd`           | Floating-point subtract                 | `0nD3`   |
| `FMUL`    | `rs`, `rd`           | Floating-point multiply                 | `0nD4`   |
| `FDIV`    | `rs`, `rd`           | Floating-point divide                   | `0nCD`   |
| `FMOD`    | `rs`, `rd`           | FLoating-point modulo                   | `0nCC`   |
| `SHL`     | `sh`, `rd`           | Shift left                              | `0nCB`   |
| `SHR`     | `sh`, `rd`           | Shift right                             | `0nCA`   |
| `AND`     | `rs`, `rd`           | Tritwise AND                            | `0nC0`   |
| `OR`      | `rs`, `rd`           | Tritwise OR                             | `0nC1`   |
| `NOT`     | `rd`                 | Tritwise NOT (or negation)              | `0nC2`   |
| `LD`      | `rs`, `rd`           | Load memory into register               | `0nC3`   |
| `LI`      | `rs`, `rd`           | Load small immediate into register      | `0nC4`   |
| `ST`      | `rs`, `rd`           | Store register into memory              | `0nBD`   |