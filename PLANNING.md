# Number representation
Termite uses 12-trit integers and 24-trit floating-point numbers. Since floating-point numbers take up 2 words of space, floating-point intructions use odd-numbered registers only  – for example, passing `r1` to a floating-point instruction will impliticly specify a floating-point number whose hi word is `r1` and lo word is `r2`.
# Processor architecture
## Memory
The 12-trit word size enables access to 531,441 words of memory. The top 19,683 words in the memory space (from `0n444444` downwards) are reserved for the system, giving 511,758 words for programming.

## CPU registers
The CPU contains 9 general-purpose 12-trit registers (r0 to r8). r8 is the program counter (PC), and r7 is the stack pointer (SP).

             
## Instructions
| Instruction |                       Meaning                   | Opcode |
| ----------- | ----------------------------------------------- | ------ |
| `NOP`       | No operation                                    | `0nDD` |
| `LD`        | Loads memory into register                      | `0nDC` |
| `LHI`       | Loads immediate into register's high tryte      | `0nDB` |
| `LLI`       | Loads immediate into register's low tryte       | `0nDA` |
| `ST`        | Stores register into memory                     | `0nD0` |
| `ADD`       | Adds two registers as integers                  | `0nD1` |
| `FADD`      | Adds two registers as floats                    | `0nD2` |
| `SUB`       | Subtracts two registers as integers             | `0nD3` |
| `FSUB`      | Subtracts two registers as floats               | `0nD4` |
| `MUL`       | Multiplies two registers as integers            | `0nCD` |
| `FMUL`      | Multiplies two registers as floats              | `0nCC` |
| `DIV`       | Divides two registers as integers               | `0nCB` |
| `FDIV`      | Divides two registers as floats                 | `0nCA` |
| `MOD`       | Takes modulo of two registers as integers       | `0nC0` |
| `FMOD`      | Takes modulo of two registers as floats         | `0nC1` |
| `SHL`       | Left-shifts a register by an amount             | `0nC2` |
| `SHR`       | Right-shifts a register by an amount            | `0nC3` |
| `NOT`       | Takes tritwise NOT (or negation) of a register  | `0nC4` |
| `AND`       | Takes tritwise AND of two registers             | `0nBD` |
| `OR`        | Takes tritwise OR of two registers              | `0nBC` |
| `BR`        | Branches to a label unconditionaly              | `0nBB` |