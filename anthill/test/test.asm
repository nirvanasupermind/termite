mov $2,%ax
mov $2,%ax
push %ax
mov $3,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L3
mov $0,%ax
_L3:
cmp $1, %ax
jne _L1
mov $4,%ax
mov $2,%ax
mov $2,%ax
push %ax
mov $3,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L4
mov $0,%ax
_L4:
cmp $1, %ax
jmp _L2
_L1:
mov $5,%ax
_L2:
mov %ax,%dx
mov $0nDC, %ax
int 0