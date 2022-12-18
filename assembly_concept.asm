; This program adds 5 and 4 and prints the result
.text
main:
    mov r1, #5
    mov r2, #4
    add r1, r2
    mov r0, r1
    add r0, 0s20 ; Add 0s20 to r0 to create TCS char code for '9'
    int 0s00 ; Print char service with r0 implicitly passed as argument