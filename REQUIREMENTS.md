WIP
# Number representation
Termite uses an 18-trit word, divided into 3 6-trit trytes. Words can be used to represent ternary integers, ternary floating-point numbers, or characters in the Termite Character Set (TCS). 


# Processor architecture

## Memory
The 18-trit word size enables access to 387,420,489 words of memory. 

## CPU registers
The CPU contains 27 general-purpose 18-trit registers (r0 to r26). r25 is the stack pointer (SP), and r26 is the program counter (PC).

             
## Instruction set
| Mnemonic  |             Instruction           |          Action           |  Opcode (sept)  |
| --------  | --------------------------------- | ------------------------- | --------------- |
| `nop`     | No operation                      |                           | `0sEEE`         |
| `sys`     | Syscall                           | (See *Syscall services*)  | `0sEEF`         |
| `add`     | Add                               | `rd := rs1 + rs2`         | `0sEFE`         |
| `sub`     | Subtract                          | `rd := rs1 - rs2`         | `0sEFF`         |
| `mul`     | Multiply                          | `rd := rs1 * rs2`         | `0sEFG`         |
| `div`     | Divide                            | `rd := rs1 / rs2`         | `0sEFH`         |
| `mod`     | Modulo                            | `rd := rs1 % rs2`         | `0sEFI`         |
| `shl`     | Left-shift                        | `rd := rs >> imm`         | `0sEFJ`         |
| `shr`     | Right-shift                       | `rd := rs << imm`         | `0sEFK`         |
| `and`     | Tritwise AND                      | `rd := rs1 & rs2`         | `0sEFL`         |
| `or`      | Tritwise OR                       | `rd := rs1 \| rs2`        | `0sEFM`         |
| `not`     | Tritwise NOT (negation)           | `rd := ~rs`               | `0sEFN`         |
| `fadd`    | Floating-point add                | `rd := rs1 + rs2`         | `0sEGE`         |
| `fsub`    | Floating-point subtract           | `rd := rs1 - rs2`         | `0sEGF`         |
| `fmul`    | Floating-point multiply           | `rd := rs1 * rs2`         | `0sEGG`         |
| `fdiv`    | Floating-point divide             | `rd := rs1 / rs2`         | `0sEGH`         |
| `fmod`    | Floating-point modulo             | `rd := rs1 % rs2`         | `0sEGI`         |
| `ld`      | Load                              | `rd := mem[rs]`           | `0sEHE`         |
| `li`      | Load 6-trit immediate             | `rd := imm`               | `0sEHF`         |
| `st`      | Store                             | `mem[rd] := rs`           | `0sEHG`         |
| `push`    | Push                              | `mem[rd] := rs`           | `0sEHG`         |
| `b`       | Branch always                     | `pc := addr`              | `0sEIE`         |
| `bz`      | Branch if zero                    | `rs == 0: pc := imm`      | `0sEIF`         |
| `bnz`     | Branch if not zero                | `rs != 0: pc := imm`      | `0sEIG`         |
| `bc`      | Branch if carry                   | `C != 0: pc := imm`       | `0sEIH`         |
## Instruction formats
#### `nop`, `sys`
<table>
    <thead>
        <tr>
            <td>17</td>
            <td>16<td>
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
    </thead>
    <tbody>
        <tr>
            <td colspan=6>opcode</td>
            <td colspan=12>Ignored by processor</td>
        </tr>
    </tbody>
</table>

### `add`, `sub`, `mul`, `div`, `mod`, `and`, `or`, `not`, `fadd`, `fsub`, `fmul`, `fdiv`
<table>
    <thead>
        <tr>
            <td>17</td>
            <td>16<td>
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
    </thead>
    <tbody>
        <tr>
            <td colspan=6>opcode</td>
            <td colspan=3>rd</td>
            <td colspan=3>rs1</td>
            <td colspan=3>rs2</td>
            <td colspan=3>Ignored by processor</td>
        </tr>
    </tbody>
</table>

#### `shl`, `shr`, `li`
<table>
    <thead>
        <tr>
            <td>17</td>
            <td>16<td>
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
    </thead>
    <tbody>
        <tr>
            <td colspan=6>opcode</td>
            <td colspan=3>rd</td>
            <td colspan=3>rs</td>
            <td colspan=6>imm</td>
        </tr>
    </tbody>
</table>

## Syscall services
|    Service    | Code in `r0` |        Arguments         | 
| ------------- | ------------ | ------------------------ |
| print int     | `0sEEEEEE`   | `r1` = Register to print |
| print float   | `0sEEEEEF`   | `r1` = Register to print |
| read int      | `0sEEEEEF`   | `r1` = Register to print |