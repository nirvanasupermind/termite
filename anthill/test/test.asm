call main
f:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov -2(%bp),%ax
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
pop %bp
ret
jmp _L2
_L1:
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov $1,%ax
pop %cx
xchg %cx,%ax
sub %cx,%ax
mov %ax,%di
call f
pop %cx
mul %cx
pop %bp
ret
_L2:
pop %bp
ret
main:
push %bp
mov %sp,%bp
mov $6,%ax
mov %ax,%di
call f
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
