b 18;
print_int:movi r-11, -81;ld r-13, r-11, 0;movi r-11, 2;st r-13, r-11, 0;movi r-11, 2;ld r-13, r-11, 0;sys 1;movi r-13, 0;mov r13, r-9;
main:
movi r-13, 50;
movi r-11, -81;
st r-13, r-11, 0;
mov r-9, r13;
addi r-9, r-9, 4;
b -6;