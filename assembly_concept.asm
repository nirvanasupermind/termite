# This program adds 5 and 4 and prints the result
main:
    ldi r0, 5;
    ldi r1, 4;
    add r0, r1;
    syscall 0n004;