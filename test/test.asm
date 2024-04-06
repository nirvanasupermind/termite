main:
movi r-13, 5;
mov r-12, r-13;
movi r-13, 5;
cmp r-12, r-13;
movi r-13, 1;
beq 2;
movi r-13, -1;
movi r-11, 0;
st r-13, r-11, 0;
movi r-11, 0;
ld r-13, r-11, 0;
sys 1; 5