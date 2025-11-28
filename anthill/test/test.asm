call main
putc:
push %bp
mov %sp,%bp
mov %di,%ax
push 0(%bp)
mov %ax,-1(%bp)
pop 0(%bp)
mov -1(%bp),%ax
mov %ax,%dx
mov $0nD0,%ax
int $0
mov %dx,%ax
pop %bp
ret
puti:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov %dx,%ax
pop %bp
ret
puts:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-2(%bp)
mov $0,%ax
mov %ax,-4(%bp)
jmp _L2
_L1:
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -4(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov %ax,%di
call putc
mov -4(%bp),%ax
mov -4(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-4(%bp)
_L2:
mov -4(%bp),%ax
mov -4(%bp),%ax
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
pop %bp
ret
main:
push %bp
mov %sp,%bp
mov $0,%ax
mov %ax,-2(%bp)
jmp _L6
_L5:
mov -2(%bp),%ax
mov %ax,%di
call puti
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-2(%bp)
_L6:
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov $3,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L7
mov $-1,%ax
_L7:
cmp $1, %ax
je _L5
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
pop %bp
ret
