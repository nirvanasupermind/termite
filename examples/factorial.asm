# Reads a number and outputs the factorial of the number 

main:
    sys 5; # Input stored into r-13
    call 6; # Currently unuspported to use the "fac" label before it is defined
    mov r-13, r-12;
    sys 1; # Print output
    sys 0; # Exit
fac: 
    # r-13 = input, r-12 = output, r-11 = loop counter
    movi r-11, 1;
    movi r-12, 1;
loop:
    mul r-12, r-12, r-11; # r-12 = r-12 * r-11
    addi r-11, r-11, 1; # r-11 = r-11 + 1
    cmp r-11, r-13;
    ble loop;
    ret;

# 20 / 5 = 4
# 20 - 5 - 5 - 5 - 5 = 0
