b 18;
test:
ld r-13, r-9, -81;
movi r-11, 0;
st r-13, r-11, 0;
movi r-11, 2;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 1;
add r-13, r-12, r-13;
mov r13, r-8;
main:
movi r-13, 5;
st r-13, r-9, -81;
mov r-8, r13;
subi r-8, r-8, 2;
b -28;
