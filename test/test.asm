main:
    sys 5;
    call 10;
    sys 1;
    movi r-13, -3270;
    sys 3;
    sys 0;
fac:
    cmpi r-13, 1;
    bgt 6;
    movi r-13, 1;    
    ret;
rec:
    movi r-12, r-13;
    subi r-13, r-13, 1;
    call fac;
    muli r-13, r-13, r-12;
    ret; 