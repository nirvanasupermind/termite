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
fputs:
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
puts:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10012
mov 10012,%ax
mov %ax,%di
call fputs
mov $10,%ax
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
mov %ax,10014
mov $1,%ax
sub $2,%sp
mov %ax,10016
mov $1,%ax
sub $2,%sp
mov %ax,10018
jmp _L5
_L4:
mov 10018,%ax
push %ax
mov 10016,%ax
pop %cx
mul %cx
mov %ax,10018
mov 10016,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10016
_L5:
mov 10016,%ax
push %ax
mov 10014,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jle _L6
mov $-1,%ax
_L6:
cmp $1, %ax
je _L4
mov 10018,%ax
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
mov %ax,10020
mov $0,%ax
sub $2,%sp
mov %ax,10022
jmp _L8
_L7:
mov 10022,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10022
_L8:
mov 10020,%ax
push %ax
mov 10022,%ax
pop %cx
add %cx,%ax
push %ax
mov 10022,%ax
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
mov 10022,%ax
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
mov %ax,10024
mov %si,%ax
mov %ax,10026
mov %dx,%ax
mov %ax,10028
mov $0,%ax
sub $2,%sp
mov %ax,10030
mov $0,%ax
sub $2,%sp
mov %ax,10032
jmp _L11
_L10:
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10026,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10030,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10030
_L11:
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
jne _L12
mov $-1,%ax
_L12:
cmp $1, %ax
je _L10
jmp _L14
_L13:
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10032,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10032,%ax
pop %cx
add %cx,%ax
push %ax
mov 10028,%ax
push %ax
mov 10032,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10032,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10032
_L14:
mov 10028,%ax
push %ax
mov 10032,%ax
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
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10032,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10024,%ax
push %ax
mov 10030,%ax
pop %cx
add %cx,%ax
push %ax
mov 10032,%ax
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
mov %ax,10034
mov %si,%ax
mov %ax,10036
mov $0,%ax
sub $2,%sp
mov %ax,10038
jmp _L17
_L16:
mov 10038,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10038
_L17:
mov 10034,%ax
push %ax
mov 10038,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov 10036,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L18
mov $-1,%ax
_L18:
cmp $1, %ax
je _L16
mov 10034,%ax
push %ax
mov 10038,%ax
pop %cx
add %cx,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
memcpy:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10040
mov %si,%ax
mov %ax,10042
mov %dx,%ax
mov %ax,10044
mov $0,%ax
sub $2,%sp
mov %ax,10046
jmp _L20
_L19:
mov 10040,%ax
push %ax
mov 10046,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10040,%ax
push %ax
mov 10046,%ax
pop %cx
add %cx,%ax
push %ax
mov 10042,%ax
push %ax
mov 10046,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10046,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10046
_L20:
mov 10046,%ax
push %ax
mov 10044,%ax
push %ax
mov $2,%ax
pop %cx
mul %cx
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L21
mov $-1,%ax
_L21:
cmp $1, %ax
je _L19
mov %bp,%sp
pop %bp
ret
main:
push %bp
mov %sp,%bp
sub $729,%sp
mov $72,%ax
mov %ax,10048
mov $101,%ax
mov %ax,10050
mov $108,%ax
mov %ax,10052
mov $108,%ax
mov %ax,10054
mov $0,%ax
mov %ax,10056
mov $10048,%ax
sub $2,%sp
mov %ax,10058
mov $46,%ax
mov %ax,10060
mov $46,%ax
mov %ax,10062
mov $46,%ax
mov %ax,10064
mov $46,%ax
mov %ax,10066
mov $0,%ax
mov %ax,10068
mov $10060,%ax
sub $2,%sp
mov %ax,10070
mov 10058,%ax
mov %ax,%di
mov 10070,%ax
mov %ax,%si
mov $3,%ax
mov %ax,%dx
call memcpy
mov 10058,%ax
mov %ax,%di
call puts
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
