call main;
putc:
push %bp
mov %sp,%bp
mov %di,%ax
push 1(%bp)
mov %ax,-0(%bp)
pop 1(%bp)
mov -0(%bp),%ax
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
mov %ax,-0(%bp)
mov -0(%bp),%ax
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
mov %ax,-0(%bp)
mov $0,%ax
mov %ax,-2(%bp)
jmp _L2
_L1:
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov -2(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov %ax,%di
call putc
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-2(%bp)
_L2:
mov -2(%bp),%ax
mov -2(%bp),%ax
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
mov $90,0
mov $101,1
push 3
mov $0,2
pop 3
mov $0,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov %ax,%di
call puti
mov $0,%ax
pop %bp
ret
pop %bp
ret
