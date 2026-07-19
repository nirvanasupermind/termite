call main
mov $0,%dx
mov $0nDD,%ax
int $0
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
mov %ax,10001
mov 10001,%ax
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
mov %ax,10003
mov 10003,%ax
fld %ax
mov $0nCA,%ax
int $0
fstp %ax
mov %bp,%sp
pop %bp
ret
fputs:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10007
mov $0,%ax
sub $2,%sp
mov %ax,10009
jmp _L2
_L1:
mov 10007,%ax
push %ax
mov 10009,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
mov %ax,%di
call putc
mov 10009,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10009
_L2:
mov 10007,%ax
push %ax
mov 10009,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $0
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
puts:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10011
mov 10011,%ax
mov %ax,%di
call fputs
ldt $10
mov %ax,%di
call putc
mov %bp,%sp
pop %bp
ret
fact:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10013
mov $1,%ax
sub $2,%sp
mov %ax,10015
mov $1,%ax
sub $2,%sp
mov %ax,10017
jmp _L5
_L4:
mov 10017,%ax
push %ax
mov 10015,%ax
pop %cx
mul %cx
mov %ax,10017
mov 10015,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10015
_L5:
mov 10015,%ax
push %ax
mov 10013,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jle _L6
mov $-1,%ax
_L6:
cmp $1, %ax
je _L4
mov 10017,%ax
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
mov $10019,%ax
mov $5314410,0(%ax)
mov $3,2(%ax)
fld %ax
fneg
fstp %ax
neg %ax
mov %ax,%di
call putf
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
