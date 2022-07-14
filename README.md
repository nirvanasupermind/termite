# termite
Termite is a stack-based virtual machine based on balanced ternary arithmetic, implemented in C++11. 

This project is very much a work-in-progress, and currently, the virtual machine is unfinished. Future plans include a toolchain featuring a lightweight operating system and compiled programming language for ternary software development, although neither have been implemented or planned out yet.

## What is balanced ternary?
Unlike the prevailing binary representation, a balanced ternary integer is in base 3, and each digit can have the values 1, 0, or −1. Since it is inconvenient to write -1 as a digit, the letter "T" is often used as a substitute. For example, decimal 11 = 3^2 + 3^1 - 3^0, thus it can be written as "11T".


