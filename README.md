![Termite icon](./icon.png)
# Termite
Termite is an emulator for a 16-trit unbalanced ternary computer written in C++11, with a clock rate of ~450 kHz. Instead of the more common binary system (base 2) where the states are (0, 1), it uses  unbalanced ternary (base 3) where the states are (0, 1, 2). A ternary digit is known as a "trit". To convert ternary data to a more compact representation, the nonary (base 9) number system is used, because each nonary digit corresponds to 2 trits. The memory of the processor is internally stored in regular binary, with each trit of memory encoded as 2 bits. This repo includes a binary called `ter`

[Architecture document](architecture.md)