main:
movi r-13, 1;
movi r-11, 0;
st r-13, r-11, 0;
mov r-10, r-13;
while0:
mov r-13, r-10;
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 2;
mul r-13, r-12, r-13;
movi r-11, 0;
st r-13, r-11, 0;
mov r-10, r-13;
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 100;
cmp r-12, r-13;
movi r-13, 1;
blt 2;
movi r-13, -1;
cmpi r-13, -1;
bne while0;
mov r-13, r-10;
sys 1;