call main
mov $0,%dx
mov $0nDD,%ax
int $0
time_hi:
push %bp
mov %sp,%bp
sub $729,%sp
mov $0nCB,%ax
int $0
mov %dx,%ax
mov %bp,%sp
mov %bp,%sp
pop %bp
ret
time_lo:
push %bp
mov %sp,%bp
sub $729,%sp
mov $0nCB,%ax
int $0
mov %bp,%sp
mov %bp,%sp
pop %bp
ret
putc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10000
mov 10000,%ax
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
mov %ax,10002
mov 10002,%ax
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
mov %ax,10004
mov 10004,%ax
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
mov %ax,10008
mov $0,%ax
sub $2,%sp
mov %ax,10010
jmp _L2
_L1:
mov 10008,%ax
push %ax
mov 10010,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov %ax,%di
call putc
mov 10010,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10010
_L2:
mov 10008,%ax
push %ax
mov 10010,%ax
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
fact:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10012
mov $1,%ax
sub $2,%sp
mov %ax,10014
mov $1,%ax
sub $2,%sp
mov %ax,10016
jmp _L5
_L4:
mov 10016,%ax
push %ax
mov 10014,%ax
pop %cx
mul %cx
mov %ax,10016
mov 10014,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10014
_L5:
mov 10014,%ax
push %ax
mov 10012,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jle _L6
mov $-1,%ax
_L6:
cmp $1, %ax
je _L4
mov 10016,%ax
mov %bp,%sp
pop %bp
ret
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
main:
push %bp
mov %sp,%bp
sub $729,%sp
mov $72,%ax
mov %ax,10018
mov $101,%ax
mov %ax,10020
mov $108,%ax
mov %ax,10022
mov $108,%ax
mov %ax,10024
mov $111,%ax
mov %ax,10026
mov $32,%ax
mov %ax,10028
mov $119,%ax
mov %ax,10030
mov $111,%ax
mov %ax,10032
mov $114,%ax
mov %ax,10034
mov $108,%ax
mov %ax,10036
mov $100,%ax
mov %ax,10038
mov $33,%ax
mov %ax,10040
mov $0,%ax
mov %ax,10042
mov $10018,%ax
mov %ax,%di
call puts
mov $10,%ax
mov %ax,%di
call putc
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
