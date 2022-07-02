# termite
Termite is a stack-based virtual machine with an 8086-style architecture based on balanced ternary arithmetic, implemented in C++11. 

Termite makes extensive use of the balanced ternary (base-3) system where numbers are represented by a digits for -1, and 0, and 1 (with -1 being represented by the letter "T" in situations where one character per digit is required). 

This system is completely incompatible with the traditonal binary system, which would minimize the potential for leakage of information and malware on ternary computers.

This project is very much a work-in-progress, and currently, the virtual machine is unfinished. Future plans include a toolchain featuring a lightweight operating system and compiled programming language for ternary software development, although neither have been implemented or planned out yet.