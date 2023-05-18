Nte: In this document, nonary numbers are represented with prefix of 0n

Termite's ISA is loosely based on early versions of ARM, but entirely ternary. Termite uses trytes (ternary bytes) of 8 trits (ternary digits), and little-endian words of 16 trits. Addresses are 1 word long, so Termite can address 3^16 = 43046721 trytes of memory.

# Registers
The processor has 27 general 16-trit registers (`r0`-`r26`). `r25` is also referred to as `lr`, the link register. `r26` is also referred to as `pc`, the program counter.

The current program status register (`cpsr`) has the following 16 trits.
* `s` (trit 0): Three's complement sign flag, 0 = negative, 1 = zero, 2 = positive
* `c` (trit 1): Carry flag
* trits 2-15: Unused

# Instructions
|Opcode|Mnemonic|Description                     |Action                        |Flags affected|
|------|--------|--------------------------------|------------------------------|--------------|
|`0n00`|`mov`   |Move                            |`rd = rs`                     |              |
|`0n01`|`movi`  |Move immediate                  |`rd = imm`                    |              |
|`0n02`|`ldr`   |Load register                   |`rd = mem[rs + imm]`          |              |
|`0n03`|`str`   |Store register                  |`mem[rd + imm] = rs`          |              |
|`0n04`|`neg`   |Threes complement negate        |`rd = -rs`                    |`s`           |
|`0n05`|`add`   |Add                             |`rd = rs + rt`                |`s`, `c`      |
|`0n06`|`addi`  |Add immediate                   |`rd = rs + imm`               |`s`, `c`      |
|`0n07`|`addc`  |Add with carry                  |`rd = rs + rt + c`            |`s`, `c`      |
|`0n08`|`addci` |Add with carry immediate        |`rd = rs + imm + c`           |`s`, `c`      |
|`0n10`|`sub`   |Subtract                        |`rd = rs - rt`                |`s`, `c`      |
|`0n11`|`subi`  |Subtract immediate              |`rd = rs - imm`               |`s`, `c`      |
|`0n12`|`subc`  |Subtract with carry             |`rd = rs - rt - c`            |`s`, `c`      |
|`0n13`|`subci` |Subtract with carry immediate   |`rd = rs - imm - c`           |`s`, `c`      |
|`0n14`|`mul`   |Multiply                        |`rd = rs * rt`                |`s`           |
|`0n15`|`muli`  |Multiply immediate              |`rd = rs * imm`               |`s`           |
|`0n16`|`not`   |Tritwise NOT                    |`rd = ~rs`                    |`s`           |
|`0n17`|`and`   |Tritwise AND                    |`rd = rs & rt`                |`s`           |
|`0n18`|`andi`  |Tritwise AND immediate          |`rd = rs & imm`               |`s`           |
|`0n20`|`or`    |Tritwise OR                     |`rd = rs \| rt`               |`s`           |
|`0n21`|`ori`   |Tritwise OR immediate           |`rd = rs \| imm`              |`s`           |
|`0n22`|`sl`    |Shift left                      |`rd = rs >> imm`              |`s`           |
|`0n23`|`asr`   |Arithmetic shift right          |`rd = rs << imm`              |`s`           |
|`0n24`|`lsr`   |Logical shift right             |`rd = rs <<< imm`             |`s`           |
|`0n25`|`b`     |Branch                          |`pc = pc + imm`               |              |
|`0n26`|`beq`   |Branch if equal                 |`pc = pc + imm` if `rd == rs` |              |
|`0n27`|`bne`   |Branch if not equal             |`pc = pc + imm` if `rd != rs` |              |
|`0n28`|`blt`   |Branch if less than             |`pc = pc + imm` if `rd < rs`  |              |
|`0n30`|`ble`   |Branch if less than or equal    |`pc = pc + imm` if `rd <= rs` |              |
|`0n31`|`bgt`   |Branch if greater than          |`pc = pc + imm` if `rd > rs`  |              |
|`0n32`|`bge`   |Branch if greater than or equal |`pc = pc + imm` if `rd >= rs` |              |
|`0n33`|`bl`    |Branch and link                 |`lr = pc; pc = pc + imm`      |              |
|`0n34`|`swi`   |Software interrupt              |                              |              |

# Instruction formats


## Software interrupt instruction
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
        <td colspan="4">opcode</td>
        <td colspan="12">interrupt</td>
    </tr>
</table>


## Load/store, immediate and shift instructions
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
        <td colspan="4">opcode</td>
        <td colspan="3">rd</td>
        <td colspan="3">rs</td>
        <td colspan="6">imm</td>
    </tr>
</table>


## All other instructions
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
        <td colspan="4">opcode</td>
        <td colspan="3">rd</td>
        <td colspan="3">rs</td>
        <td colspan="3">rt</td>
        <td colspan="3">unused</td>
    </tr>
</table>


# System calls
System call API is accesible via executing the instruction `swi 0`.
|`r0`|Description                     |Arguments                                   |Result                               |
|----|--------------------------------|--------------------------------------------|-------------------------------------|
|0   |Terminate program               |                                            |                                     |
|1   |Read character from stdin       |                                            |low tryte of `r1` = character code   |
|2   |Write character to stdout       |low tryte of `r1` = character code          |                                     |
|3   |Get UNIX timestamp milliseconds |                                            |`r1` = low word , `r2` = high word   |

# Character encoding
Because nearly all existing standards such as ASCII are binary-based, Termite uses a custom character encoding with each character as 1 tryte. As of Termite 1.0, only the first 81 out of 6561 possible characters have been allocated, with the rest left undefined.
Below is a table of the current character encoding with codes in nonary:
|     |0  |1  |2  |3  |4  |5  |6  |7  |8  |
|-----|---|---|---|---|---|---|---|---|---|
|000x |NUL|BEL|BS |HT |LF |VT |FF |CR |SUB|
|001x |SP |-  |:  |;  |'  |,  |.  |?  |!  |
|002x |0  |1  |2  |3  |4  |5  |6  |7  |8  |
|003x |9  |A  |B  |C  |D  |E  |F  |G  |H  |
|004x |I  |J  |K  |L  |M  |N  |O  |P  |Q  |
|005x |R  |S  |T  |U  |V  |W  |X  |Y  |Z  |
|006x |_  |a  |b  |c  |d  |e  |f  |g  |h  |
|007x |i  |j  |k  |l  |m  |n  |o  |p  |q  |
|008x |r  |s  |t  |u  |v  |w  |x  |y  |z  |