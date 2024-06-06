b 48;
print_int:
movi r-11, -81;
ld r-13, r-11, 0;
movi r-11, 2;
st r-13, r-11, 0;
sys 1;mov r13, r-9;
print_char:
movi r-11, -81;
ld r-13, r-11, 0;
movi r-11, 3;
st r-13, r-11, 0;
sys 3;mov r13, r-9;
sqr:
movi r-11, -81;
ld r-13, r-11, 0;
movi r-11, 5;
st r-13, r-11, 0;
movi r-11, 5;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-11, 5;
ld r-13, r-11, 0;
mul r-13, r-12, r-13;
mov r13, r-9;
mov r13, r-9;
main:
movi r-13, 10;
movi r-11, 5;
st r-13, r-11, 0;
movi r-13, 5;
movi r-11, 7;
st r-13, r-11, 0;
movi r-11, 7;
ld r-13, r-11, 0;
ld r-13, r-13, 0;
movi r-11, -81;
st r-13, r-11, 0;
mov r-9, r13;
addi r-9, r-9, 4;
b -76;
mov r13, r-9;
