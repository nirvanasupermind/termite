uWIP
# Number representation

# Processor architecture

## Memory
The 12-trit word size enables access to 531,441 words of memory. 

## CPU registers
The CPU contains 27 general-purpose 12-trit registers (`r0` to `r26`). `r25` is the stack pointer (`sp`), and `r26` is the program counter (`pc`).

## Addressing modes

| Name               | Example       | Description                                  |
| ------------------ | ------------- | -------------------------------------------- |
| Immediate          | `#x`          | `x` is the operand                           |
| Absolute           | `x`           | `x` is the address of the operand            | 
| Register           | `rx`          | `rx` contains the operand                    | 


## Processor status word

## Instruction set
| Mnemonic | Operation                                                  |
| -------- | ---------------------------------------------------------- |
| `nop`    | Move: `dest <- src`                                        |
| `mov`    | Move: `dest <- src`                                        |
| `add`    | Add: `dest <- dest + src`                                  |
| `sub`    | Subtract: `dest <- dest - src`                             |
| `mul`    | Multiply: `dest <- dest * src`                             |
| `umul`   | Unsigned multiply: `dest <- dest * src`                    |
| `div`    | Divide: `dest <- dest / src`                               |
| `udiv`   | Unsigned divide: `dest <- dest / src`                      |
| `mod`    | Modulo: `dest <- dest % src`                               |
| `umod`   | Unsigned modulo: `dest <- dest % src`                      |
| `and`    | Tritwise AND: `dest <- dest & src`                         |
| `or`     | Tritwise OR: `dest <- dest | src`                          |
| `xor`    | Tritwise XOR: `dest <- dest ^ src`                         |
| `asl`    | Arithmetic shift left: `dest <- dest >> src`               |
| `asr`    | Arithmetic shift right: `dest <- dest << src`              |
| `lsr`    | Logical shift right: `dest <- dest << src`                 |
| `cmp`    | Compare: `set-flags(dest - src)`                           |
| `jmp`    | Jump: `pc <- addr`                                         |
| `je`     | Jump if equal (`S == 0`)                                   |
| `jne`    | Jump if not equal (`S == 1 | S == 2`)                      |
| `jl`     | Jump if less (`S == 2`)                                    |
| `jg`     | Jump if greater (`S == 1`)                                 |
| `jle`    | Jump if less than or equal (`S == 2 | S == 0`)             |
| `jge`    | Jump if greater than or equal (`S == 1 | S == 0`)          |
| `jc`     | Jump if carry (`C == 1 | C == 2`)                          |
| `hlt`    | Halt                                                       |