mov dx, 12
call f
mov ax, 0nDC
int 0
mov dx, 0
mov ax, 0nDD
int 0
f:
add dx, 1
ret