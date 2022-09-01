The Termite architecture is designed for a small ternary computer with a 12-trit word and a 19,683 word address space.

# Data Representations
The basic 12-trit word can be interpreted as an unsigned integer or a 3's complement signed integer.
They can be expressed as a decimal (base 10), ternary (base 3), or heptavigesimal (base 27) number, or a
a single character in the Termite Character Set (TCS).

# Architecture

## Registers
There are 27 registers, all of which are 1 word wide, which have been assigned as follows:
- General-purpose registers (`r0` - `r22`)
- Stack pointer (`sp` / `r23`)
- Program counter (`pc` / `r24`)
- Instruction register (`ir` / `r25`)
- Status register (`sr` / `r26`)

## Flags
The status register contains the following 1-trit flags:
- Zero flag (`Z`): Indicates if an arithmetic/logic instruction results in 0
- Carry flag (`C`): Stores the carry of an `add` instruction
- Overflow flag (`O`): Indicates if an arithmetic/logic instruction causes an overflow
- Negative flag (`N`): Indicates if an arithmetic/logic instruction results in a negative number

## Instruction Set
- No operation (`nop`): Stores a register's value into a memory address
- Store (`st`): Stores a register's value into a memory address
- Load (`ld`): Loads a memory address's value into a register
- Load immediate (`ldi`): Loads an immediate value into a register
- Push (`push`): Pushes a register's value to the top of the stack
- Pop (`pop`): Pops the top of the stack into a register
- Negate (`neg`): Loads the negation of a register into the destination
- Add (`add`): Loads the sum of two registers into the destination
- Subtract (`sub`): Loads the difference of two registers into the destination
- Multiply (`mul`): Loads the product of two registers into the destination
- Multiply unsigned (`mulu`): Loads the unsigned product of two registers into the destination
- Divide (`div`): Loads the quotient of two registers into the destination
- Divide unsigned (`divu`): Loads the unsigned quotient of two registers into the destination
- Tritwise NOT (`not`): Loads the tritwise NOT of a register into the destination
- Tritwise AND (`and`): Loads the tritwise AND of two registers into the destination
- Tritwise OR (`or`): Loads the tritwise OR of two registers into the destination
- Tritwise XOR (`xor`): Loads the tritwise XOR of two registers into the destination
- Left-shift (`ls`): Loads the left-shift of a register into the destination
- Right-shift (`rs`): Loads the right-shift of a register into the destination
- Left-shift unsigned (`lsu`): Loads the unsigned left-shift of a register into the destination
- Right-shift unsigned  (`rsu`): Loads the unsigned right-shift of a register into the destination
- Jump (`jmp`): Jumps to a label unconditionally
- Jump if zero (`jmpz`): Jumps to a label if the processor's zero flag is true
- Jump if carry (`jmpc`): Jumps to a label if the processor's carry flag is true
- Syscall (`sys`): Handles high-level operations including I/O

## Instruction Format
All instructions have a fixed width of 1 word (formats listed here with smaller sizes are padded to 1 word):
-  `nop`: 3-trit opcode
-  `st`: 3-trit opcode, 3-trit register, 6-trit address
-  `ld`: 3-trit opcode, 6-trit address, 3-trit register
-  `ldi`: 3-trit opcode, 3-trit register, 6-trit immediate value
-  `neg`, `not`: 3-trit opcode, 3-trit source register, 3-trit destination register
-  `add`, `sub`, `mul`, `mulu`, `div`, `divu`, `and`, `or`, `xor`, `ls`, `rs`, `lsu`, `rsu`: 
    3-trit opcode, 3-trit source register #1, 3-trit source register #2, 2, 3-trit destination register
- `jmp`, `jmpz`, `jmpc`: 3-trit opcode, 9-trit address
- `sys`: 3-trit opcode, 9-trit syscall code

## Syscall Services
- `0`: Exits cleanly
- `1`: Inputs decimal value into register
- `2`: Inputs ternary value into register
- `3`: Inputs heptavigesimal value into register
- `4`: Inputs TCS character into register
- `5`: Outputs register as decimal value
- `6`: Outputs register as ternary value
- `7`: Outputs register as heptavigesimal value
- `8`: Outputs register as TCS character