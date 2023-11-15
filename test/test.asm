main:
    movi r0, 0;
    cmpi r0, 10;
    bne 2;
    sys 0;
    addi r0, 1;
