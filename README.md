![Termite icon](./icon.png)
# Termite
Version 1.0

Termite is an emulator for a 16-trit unbalanced [ternary](https://en.wikipedia.org/wiki/Ternary_numeral_system) (base 3) computer written in C++11, with a clock rate of ~450 kHz. Termite uses trytes of 8 trits and big-endian words of 16 trits. Addresses are 1 word long, so Termite can address 3^16 = 43046721 trytes of memory. Some example files you can run with `teremu` are provided in the examples directory.

[Documentation for Termite](documentation.md)

## Included command-line programs
These can be built using `make` (Mac/Linux only, and may require root permission).

* `teremu`: For running Termite machine code executable files. -v option can be added for verbose mode, where the values of all registers are printed after each instruction runs. File format for Termite executables is .texe.

* `terasm`: For transpiling Termite assembly files into executable files. 

## Future ideas
* High-level C-like programming language which compiles into Termite assembly and.

## Changelog
* 1.1 (2023-12-24): `terasm` assembler, Added instructions like `xor` and `xori`
* 1.0 (2023-07-09): Initial release, no assembler yet