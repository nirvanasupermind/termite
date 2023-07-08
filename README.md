![Termite icon](./icon.png)
# Termite
Version 1.0

Termite is an emulator for a 16-trit unbalanced [ternary](https://en.wikipedia.org/wiki/Ternary_numeral_system) computer written in C++11, with a clock rate of ~450 kHz. 

Termite is loosely based on the design of early ARM processors, but is built on ternary (base 3) instead of binary, using three ternary digits (or "trits") {0, 1, 2}. Nonary (base 9, where each digit is two trits) can be used for compact representation of ternary, similar to how the hexadecimal system is used in place of binary.  

Termite uses a tryte (ternary byte) width of 8 trits, and a word width of 16 trits. This allows for 3^16 = 43,046,721 trytes of memory.

[Architecture document](architecture.md)
