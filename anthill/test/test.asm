call main
fac:
mov %di,%ax
mov %ax,2
mov 2,%ax
mov 2,%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L3
mov $0,%ax
_L3:
cmp $1, %ax
jne _L1
mov $1,%ax
ret
jmp _L2
_L1:
mov 2,%ax
mov 2,%ax
push %ax
mov 4,%ax
mov 2,%ax
mov 2,%ax
push %ax
mov $1,%ax
pop %cx
xchg %cx,%ax
sub %cx,%ax
mov %ax,%di
call fac
pop %cx
mul %cx
ret
_L2:
main:
mov 4,%ax
mov $5,%ax
mov %ax,%di
call fac
mov %ax,%dx
mov $0nDC, %ax
int 0
mov $0,%ax
ret