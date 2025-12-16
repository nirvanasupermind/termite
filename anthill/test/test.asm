call main
putc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov %ax,%dx
mov $0nD0,%ax
int $0
mov %dx,%ax
mov %bp,%sp
pop %bp
ret
puti:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov %dx,%ax
mov %bp,%sp
pop %bp
ret
puts:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,-2(%bp)
mov $0,%ax
sub $2,%sp
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
mov %ax,%di
call putc
mov -4(%bp),%ax
mov -4(%bp),%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,-4(%bp)
_L2:
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -4(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -4(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L3
mov $-1,%ax
_L3:
cmp $1, %ax
je _L1
mov %bp,%sp
pop %bp
ret
main:
push %bp
mov %sp,%bp
sub $729,%sp
mov $72,%ax
mov %ax,1
mov $101,%ax
mov %ax,3
mov $108,%ax
mov %ax,5
mov $108,%ax
mov %ax,7
mov $111,%ax
mov %ax,9
mov $32,%ax
mov %ax,11
mov $119,%ax
mov %ax,13
mov $111,%ax
mov %ax,15
mov $114,%ax
mov %ax,17
mov $108,%ax
mov %ax,19
mov $100,%ax
mov %ax,21
mov $33,%ax
mov %ax,23
mov $0,%ax
mov %ax,25
mov $1,%ax
sub $2,%sp
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov %ax,%di
call puts
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
