call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $10,%ax
mov %ax,0
mov $0,%ax
mov %ax,2
jmp _L2
_L1:
mov 0,%ax
mov 0,%ax
push %ax
mov $2,%ax
pop %cx
mul %cx
mov %ax,0
mov 2,%ax
mov 2,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,2
_L2:
mov 2,%ax
mov 2,%ax
push %ax
mov $10,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L3
mov $0,%ax
_L3:
cmp $1, %ax
je _L1
mov 0,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
