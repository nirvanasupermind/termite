putc:
mov %di,%ax
push 1
mov %ax,0
pop 1
mov 0,%ax
mov %ax,%dx
mov $0nD0,%ax
int $0
mov %dx,%ax
ret
puti:
mov %di,%ax
mov %ax,1
mov %di,%dx
mov $0nDC,%ax
jmp after_puti
puts:
mov %di,%ax
mov %ax,3
mov $0,%ax
mov %ax,5
jmp _L2
_L1:
mov 3,%ax
mov 3,%ax
push %ax
mov 5,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov %ax,%di
call putc
mov 5,%ax
mov 5,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,5
_L2:
mov 5,%ax
mov 5,%ax
push %ax
mov $10,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L3
mov $-1,%ax
_L3:
cmp $1, %ax
je _L1
ret
main:
mov $5,%ax
mov %ax,%di
jmp puti
after_puti:
mov $0,%ax
ret
ret
