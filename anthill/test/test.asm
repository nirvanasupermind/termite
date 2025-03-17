mov $5,%ax
jmp _L2
_L1:
_L2:
push %ax
mov $100,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L3
mov $0,%ax
_L3:
cmp $1, %ax
je _L1
mov %ax,%dx
mov $0nDC, %ax
int 0