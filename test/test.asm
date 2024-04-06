main:
movi r-12, 6;
movi r-13, 7;
cmp r-12, r-13;
movi r-13, -1;
blt 2;
movi r-13, 1;
sys 1;