![Termite icon](./icon.png)
# Termite
Version 1.0

Termite is an emulator for a 16-trit unbalanced [ternary](https://en.wikipedia.org/wiki/Ternary_numeral_system) (base 3) computer written in C++11, with a clock rate of ~450 kHz. Termite uses trytes of 8 trits and little-endian words of 16 trits. Addresses are 1 word long, so Termite can address 3^16 = 43046721 trytes of memory.

Ternary is the base-3 numeral system, using three digits {0, 1, 2}. Ternary digits are often referred to as "trits", analogous to bit. For example, the string "102" in ternary represents 1 × 3<sup>2</sup> + 0 ×  3<sup>1</sup> + 2 × 3<sup>0</sup>, or 11 in decimal. The ternary analog of boolean logic is  [Kleene logic](https://en.wikipedia.org/wiki/Three-valued_logic#Kleene_and_Priest_logics), which uses a third "unknown" state in addition to true and false. 

To store ternary data on a binary computer, Termite internally uses a system known as [binary-coded ternary](https://en.wikipedia.org/wiki/Ternary_numeral_system#Binary-coded_ternary) (BCT) where each trit is mapped to two bits. Additionally, the nonary (base 9) number system, where each nonary digit is two ternary digits, is used to provide more compact representation of ternary, analogous to how hexadecimal is used for binary.
 
Currently, Termite does not have an assembler, alhough there is an exectuable called `ter` for running machine code files expressed in BCT, which can be built using the makefile.

[Architecture document](architecture.md)

