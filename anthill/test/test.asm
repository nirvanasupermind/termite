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
putf:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,-4(%bp)
mov -4(%bp),%ax
fld %ax
mov $0nCA,%ax
int $0
fstp %ax
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
mov $1,%ax
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
getc:
push %bp
mov %sp,%bp
sub $729,%sp
mov $0,%dx
mov $0nCC,%ax
int $0
mov %dx,%ax
mov %bp,%sp
mov %bp,%sp
pop %bp
ret
geti:
push %bp
mov %sp,%bp
sub $729,%sp
mov $0nD3,%ax
int $0
mov %dx,%ax
mov %bp,%sp
mov %bp,%sp
pop %bp
ret
strlen:
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
mov -4(%bp),%ax
mov -4(%bp),%ax
push %ax
mov $1,%ax
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
mov -4(%bp),%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
strcat:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,-2(%bp)
mov %si,%ax
mov %ax,-4(%bp)
mov $72,%ax
mov %ax,0
mov $0,%ax
mov %ax,2
mov $0,%ax
sub $2,%sp
mov %ax,-6(%bp)
mov $0,%ax
sub $2,%sp
mov %ax,-8(%bp)
mov $0,%ax
sub $2,%sp
mov %ax,-10(%bp)
jmp _L5
_L4:
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
push %ax
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov -8(%bp),%ax
mov -8(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-8(%bp)
_L5:
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L6
mov $-1,%ax
_L6:
cmp $1, %ax
je _L4
jmp _L8
_L7:
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
push %ax
mov -4(%bp),%ax
mov -4(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov -8(%bp),%ax
mov -8(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-8(%bp)
mov -10(%bp),%ax
mov -10(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-10(%bp)
_L8:
mov -4(%bp),%ax
mov -4(%bp),%ax
push %ax
mov -10(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L9
mov $-1,%ax
_L9:
cmp $1, %ax
je _L7
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov -6(%bp),%ax
mov -6(%bp),%ax
push %ax
mov -8(%bp),%ax
pop %cx
add %cx,%ax
push %ax
mov $0,%ax
pop %bx
mov %ax,0(%bx)
mov -6(%bp),%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
main:
push %bp
mov %sp,%bp
sub $729,%sp
mov $72,%ax
mov %ax,8
mov $101,%ax
mov %ax,10
mov $108,%ax
mov %ax,12
mov $108,%ax
mov %ax,14
mov $111,%ax
mov %ax,16
mov $32,%ax
mov %ax,18
mov $0,%ax
mov %ax,20
mov $8,%ax
mov %ax,%di
mov $119,%ax
mov %ax,22
mov $111,%ax
mov %ax,24
mov $114,%ax
mov %ax,26
mov $108,%ax
mov %ax,28
mov $100,%ax
mov %ax,30
mov $0,%ax
mov %ax,32
mov $22,%ax
mov %ax,%si
call strcat
mov %ax,%di
call puts
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
