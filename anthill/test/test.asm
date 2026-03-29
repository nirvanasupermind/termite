call main
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
mov 10008,%ax
push %ax
mov 10010,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov %ax,%di
call putc
mov 10010,%ax
mov 10010,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10010
_L2:
mov 10008,%ax
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
mov 10016,%ax
push %ax
mov 10014,%ax
pop %cx
mul %cx
mov %ax,10016
mov 10014,%ax
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
strlen:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10018
mov $0,%ax
sub $2,%sp
mov %ax,10020
jmp _L8
_L7:
mov 10020,%ax
mov 10020,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10020
_L8:
mov 10018,%ax
mov 10018,%ax
push %ax
mov 10020,%ax
pop %cx
add %cx,%ax
mov 10018,%ax
mov 10018,%ax
push %ax
mov 10020,%ax
pop %cx
add %cx,%ax
push %ax
mov 10020,%ax
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
mov 10020,%ax
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
mov %ax,10022
mov %si,%ax
mov %ax,10024
mov %dx,%ax
mov %ax,10026
mov $0,%ax
sub $2,%sp
mov %ax,10028
mov $0,%ax
sub $2,%sp
mov %ax,10030
jmp _L11
_L10:
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
push %ax
mov 10024,%ax
mov 10024,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10028,%ax
mov 10028,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10028
_L11:
mov 10024,%ax
mov 10024,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L12
mov $-1,%ax
_L12:
cmp $1, %ax
je _L10
jmp _L14
_L13:
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10026,%ax
mov 10026,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10030,%ax
mov 10030,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10030
_L14:
mov 10026,%ax
mov 10026,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L15
mov $-1,%ax
_L15:
cmp $1, %ax
je _L13
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
mov 10022,%ax
mov 10022,%ax
push %ax
mov 10028,%ax
pop %cx
add %cx,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov $0,%ax
pop %bx
mov %ax,0(%bx)
mov %bp,%sp
pop %bp
ret
strchr:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10032
mov %si,%ax
mov %ax,10034
mov $0,%ax
sub $2,%sp
mov %ax,10036
jmp _L17
_L16:
mov 10036,%ax
mov 10036,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10036
_L17:
mov 10032,%ax
mov 10032,%ax
push %ax
mov 10036,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov 10034,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L18
mov $-1,%ax
_L18:
cmp $1, %ax
je _L16
mov 10032,%ax
mov 10032,%ax
push %ax
mov 10036,%ax
pop %cx
add %cx,%ax
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
mov $0,%ax
mov %ax,10038
mov $0,%ax
mov %ax,10040
mov $0,%ax
mov %ax,10042
mov $0,%ax
mov %ax,10044
mov $10038,%ax
sub $2,%sp
mov %ax,10046
mov 10046,%ax
mov %ax,%di
mov $97,%ax
mov %ax,10048
mov $0,%ax
mov %ax,10050
mov $10048,%ax
mov %ax,%si
mov $98,%ax
mov %ax,10052
mov $99,%ax
mov %ax,10054
mov $0,%ax
mov %ax,10056
mov $10052,%ax
mov %ax,%dx
call strcat
mov 10046,%ax
mov %ax,%di
call puts
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
