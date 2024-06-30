b 54;
f:
mov r-13, r-8;
movi r-11, 0;
st r-13, r-11, 0;
movi r-11, 0;
ld r-13, r-11, 0;
sys 1;
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 0;
cmp r-12, r-13;
movi r-13, 1;
beq 2;
movi r-13, -1;
cmpi r-13, -1;
bne 4;
movi r-13, 1;
ret;
_endif0:
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 1;
sub r-13, r-12, r-13;
mov r-8, r-13;
call f;
ret;
ret;
main:
movi r-13, 2;
mov r-8, r-13;
call f;
sys 1;
movi r-13, 0;
sys 0;
ret;
