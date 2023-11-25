main:
    sys 5; # Read input
    call 6; # Currently unuspported to use the "sqr" label before it is defined
    mov r-13, r-12;
    sys 1; # Print output
    sys 0; # Exit program
sqr:
    # Using r-13 as input, r-12 as output
    mul r-12, r-13, r-13;  # r-12 = r-13 * r-13
    ret;