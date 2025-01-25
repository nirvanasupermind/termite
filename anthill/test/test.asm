b 0;
main:
push r-9;
mov r-9, r12;
sub r-9, 81;
movi r-13, 200;
sys 1;
movi r-13, 0;
sys 0;
mov r12, r-9;
pop r-9;
ret;
