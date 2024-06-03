b 20;
test:
movi r-11, -81;
ld r-13, r-11, 0;
movi r-11, 0;
st r-13, r-11, 0;
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 1;
add r-13, r-12, r-13;
mov r13, r-9;
main:
movi r-13, 5;
movi r-11, -81;
st r-13, r-11, 0;
mov r-9, r13;
addi r-9, r-9, 4;
b -32;
movi r-11, 4;
st r-13, r-11, 0;
movi r-11, 2;
ld r-13, r-11, 0;
sys 1;
