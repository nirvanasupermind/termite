# Mathematical background
The balanced ternary (base 3) system uses 3 digits, -1, 0 and 1. Typically, -1 is assigned to `false`, 0 to `unknown`, and 1 to `true`. Since it is inconvenient to write -1 as a digit, the letter A is used for this purpose in Termite. Each position in a balanced ternary number represents a power of 3. For example, `10A1` in balanced ternary represents 1\*3^3 + 0\*3^2  + (-1)\*3^1 + 1\*3^0, which is 25 in decimal. The balanced ternary system can also represent negative numbers without a separate minus sign–for example, `A1A` is (-1)\*3^2 + 1\*3^1 + (-1)\*3^0, or -7 in decimal.

The balanced nonary (base 9) system uses 9 digits, -4, -3, -2, -1, 0, 1, 2, 3, and 4. The negative digits -4, -3, -2, and -1 are represented as D, C, B, and A in Termite. Balanced nonary may be used as a way to shorten balanced ternary in the same way hexadecimal is used to shorten binary, because each balanced nonary digit corresponds to a pair of balanced ternary digits:
```
D = AA
C = A0
B = A1
A = 0A
0 = 00
1 = 01
2 = 1A
3 = 10
4 = 11
```

For example, `10A1` in balanced ternary is `3B` in balanced nonary.

# Memory
## Data formats
The smallest unit of memory is 8 trits, which is referred to as a "tryte". Each word is 16 trits or 2 trytes. 16-trit words are stored in little-endian format, with the least significant tryte placed at the lower memory address. 

There is a 16-trit address system which allows access to 3^16 (43,046,721) trytes of memory.

# CPU registers
There are 9 general-purpose registers internally numbered -4 to 4. Unlike in x86, the names for registers and instructions are case-sensitive (must be all-lowercase).

-4: Accumulator (`ax`)

-3: Base register (`bx`)

-2: Counter register (`cx`)

-1: Stack pointer register (`sp`)

0: Stack base pointer register (`bp`)

1: Destination index register (`di`)

2: Source index register (`si`)

3: Data register (`dx`)

4: Instruction pointer (`ip`) (unlike in x86, it is a GPR here)


## Flags register

There is also the special `flags` register for holding CPU flags which is 16 trits wide and has the following flags:

* Trit 0 = CF (Carry flag):  Set if there is a leftover carry/borrow which there isn't room for after an addition, subtraction, or compare instruction.
* Trit 1 = SF (Sign flag): Set to -1 if the result of an operation is negative, 0 if it is 0, and 1 if it is positive.

The other trits are currently unused. The `flags` register can only be get/set through the `pushf`and `popf` instructions.

# Addressing modes
There are 4 addressing modes supported. The addressing mode takes up 2 trits in the instruction format.

|Trit|Addressing mode    |Example    |Description|
|----|-------------------|-----------|-----------|
|`D` |Immediate          |`1`        |The operand is a supplied constant|
|`C` |Register           |`ax`       |The operand is in the register|
|`B` |Displacement       |`[1]`      |The operand's address is a supplied constant|
|`A` |Indexed            |`[ax+1]`   |The operand's address is the value of the register plus a supplied constant|

The encoding of the addressing mode is as follows:
<table>
  <tr>
    <td>3</td>
    <td>2</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td colspan="2">mode (2)</td>
    <td colspan="2">register (2)</td>
</tr>
</table>

# Instruction set
Note: In the "Action" column, `[n]` refers to the value located at address n

Note 2: Logical/shift operations do not work the same way as normal, because they operate on ternary and three-valued logic. a << b = a * 3^b instead of a * 2^b

|Opcode (nonary)|Mnemonic|Description                       |Operands                              |Action                              |
|---------------|--------|----------------------------------|--------------------------------------|------------------------------------|
|`DD`           |`mov`   |Move                              |`dest` (reg/idx), `src `(imm/reg/idx) |`dest = src`                        |
|`DC`           |`push`  |Push word onto stack              |`src` (imm/reg/idx)                   |`sp = sp - 2; [sp] = src`           |
|`DB`           |`pop`   |Pop word off stack and store it   |`dest` (reg/idx)                      |`dest = [sp]; sp = sp + 2`          |
|`DA`           |`pushf` |Push flag register on-to stack     |No operands                          |`sp = sp - 2; [sp] = flags`         |
|`D0`           |`popf`  |Pop the stack top to flag register|No operands                           |`flags = [sp]; sp = sp + 2`         |
|`D1`           |`and`   |Trit-wise logical AND             |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest & src`                 |
|`D2`           |`or`    |Trit-wise logical OR              |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest \| src`                |
|`D3`           |`xor`   |Trit-wise logical XOR             |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest ^ src`                 |
|`D4`           |`shl`   |Shift left                        |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest << src`                |
|`CD`           |`shr`   |Shift right                       |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest >> src`                |
|`CC`           |`add`   |Add                               |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest + src`                 |
|`CB`           |`adc`   |Add with carry                    |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest + src + CF`            |
|`CA`           |`sub`   |Subtract                          |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest + src`                 |
|`C0`           |`sbb`   |Subtract with borrow              |`dest` (reg/idx), `src` (imm/reg/idx) |`dest = dest - src - CF`            |
|`C1`           |`mul`   |Multiply                          |`src` (reg/idx)                       |`(dx ax) = ax * src` (`dx` stores high word of the 2-word result, `ax` stores low word)|
|`C2`           |`div`   |Divide                            |`src` (reg/idx)                       |`ax = ax / src; dx = ax % src`      |
|`C3`           |`neg`   |Negate/trit-wise logical NOT      |`src` (reg/idx)                       |`src = -src`                        |
|`C4`           |`cmp`   |Compare                           |`dest` (reg/idx), `src` (imm/reg/idx) |`set-flags(dest - src)`             |
|`BD`           |`call`  |Call procedure                    |`dest` (imm)                          |`sp = sp - 2; [sp] = ip; ip = dest;`|=
|`BC`           |`ret`   |Return from procedure             |No operands                           |`ip = [sp]; sp = sp + 2`            |
|`BB`           |`jmp`   |Unconditional jump                |`dest` (imm)                          |`ip = dest`                         |
|`BA`           |`jl`    |Jump if less than                 |`dest` (imm)                          |`ip = dest` if `SF < 0`             |
|`B0`           |`jle`   |Jump if less than or equal        |`dest` (imm)                          |`ip = dest` if `SF <= 0`            |
|`B1`           |`jg`    |Jump if greater than              |`dest` (imm)                          |`ip = dest` if `SF > 0`             |
|`B2`           |`jge`   |Jump if greater than or equal     |`dest` (imm)                          |`ip = dest` if `SF >= 0`            |
|`B3`           |`je`    |Jump if equal                     |`dest` (imm)                          |`ip = dest` if `SF == 0`            |
|`B4`           |`jne`   |Jump if not equal                 |`dest` (imm)                          |`ip = dest` if `SF != 0`            |
|`AD`           |`jc`    |Jump if carry                     |`dest` (imm)                          |`ip = dest` if `CF != 0`            |
|`AC`           |`jnc`   |Jump if not carry                 |`dest` (imm)                          |`ip = dest` if `CF == 0`            |
|`AB`           |`int`   |Software interrupt                |`vec` (imm)                           |Call the interrupt handler with interrupt vector `vec` (currently this is just simulated by an if-statement in the emulator)|

# Instruction format
All instructions are 3 words in length. The first word is the main part of the instruction, the other 2 words are used to store single-word constants. In 1-operand instructions, any single-word constant which is required for the operand (if it is in immediate, displacement or indexed addressing mode) will be stored in the second word. In 2-operand instructions, any single-word constant which is required for the first operand will be stored in the second word, and single-word. Some instructions will not require all of the 3 words, in that case the unused words are padded with 0s. Padding out every instruction to 3 words is wasteful, but it makes the CPU much easier to implement by making all the instructions a fixed width, and memory is not much of a concern for this emulator currently so it is like this for now.
0-operand instructions:
<table>
  <tr>
    <td>15</td>
    <td>14</td>
    <td>13</td>
    <td>12</td>
    <td>11</td>
    <td>10</td>
    <td>9</td>
    <td>8</td>
    <td>7</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>2</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td colspan="4">opcode (4)</td>
    <td colspan="12">unused (12)</td>
  </tr>
</table>

1-operand instructions:

<table>
  <tr>
    <td>15</td>
    <td>14</td>
    <td>13</td>
    <td>12</td>
    <td>11</td>
    <td>10</td>
    <td>9</td>
    <td>8</td>
    <td>7</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>2</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td colspan="4">opcode (4)</td>
    <td colspan="4">operand (4)</td>
    <td colspan="8">unused (8)</td>
</tr>
</table>


2-operand instructions:

<table>
  <tr>
    <td>15</td>
    <td>14</td>
    <td>13</td>
    <td>12</td>
    <td>11</td>
    <td>10</td>
    <td>9</td>
    <td>8</td>
    <td>7</td>
    <td>6</td>
    <td>5</td>
    <td>4</td>
    <td>3</td>
    <td>2</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td colspan="4">opcode (4)</td>
    <td colspan="4">operand1 (4)</td>
    <td colspan="4">operand2 (4)</td>
    <td colspan="4">unused (4)</td>
</tr>
</table>




# Interrupts
There is only one interrupt vector which can be accessed by calling `int 0` and leads to the main API (this is analogous to `int 21h` for DOS API on x86). The following subfunctions are provided by `int 0` depending on the value of `ax`:
|`ax` (nonary)  |Description                               |Operands                  |
|---------------|------------------------------------------|--------------------------|
|`DD`           |Exit program with `dx` as code (zero for success, nonzero for failure)           |`dx`                      |
|`DC`           |Print `dx` as decimal number              |`dx`                      |
|`DB`           |Print `dx` as ternary number              |`dx`                      |
|`DA`           |Print `dx` as nonary number               |`dx`                      |
|`D0`           |Print `dx`'s low tryte as character       |`dx`                      |
|`D1`           |Print `dx`'s high tryte as character      |`dx`                      |
|`D2`           |Print all registers (like in verbose mode)|No operands               |
|`D3`           |Input decimal number into `dx`            |No operands               |
|`D4`           |Input ternary number into `dx`            |No operands               |
|`CD`           |Input nonary number into `dx`             |No operands               |
|`CC`           |Input character into `dx`'s low tryte     |No operands               |
|`CB`           |Input character into `dx`'s high tryte    |No operands               |
|`CA`           |Get current 2-word Unix timestamp in milliseconds (low word stored in `ax`, high word stored in `dx`)|No operands               |