main:
movi r-13, 5;
movi r-11, 0;
st r-13, r-11, 0;
movi r-13, 0;
movi r-11, 2;
st r-13, r-11, 0;
movi r-11, 2;
ld r-13, r-11, 0;
ld r-13, r-13, 0;
sys 1;