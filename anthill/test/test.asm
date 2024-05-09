_funcmain:
movi r-13, 5;
lshi r-13, r-13, 8;
rshi r-13, r-13, 8;
movi r-11, 0;
st r-13, r-11, 0;
movi r-11, 0;
ld r-13, r-11, 0;
mov r-12, r-13;
movi r-13, 1;
add r-13, r-12, r-13;
