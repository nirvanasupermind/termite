mov $5,%ax
mov %ax,2
jmp _L2
_L1:
mov 2,%ax
mov 2,%ax
push %ax
mov 2,%ax
pop %cx
mul %cx,%ax
mov %ax,2
mov 2,%ax
_L2:
mov 2,%ax
mov 2,%ax
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
mov 2,%ax
mov %ax,%dx
mov $0nDC,%ax
int 0