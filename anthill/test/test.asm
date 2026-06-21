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
mov 0(%ax),%ax
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
mov %ax,10011
mov 10011,%ax
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
strlen:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10019
mov $0,%ax
sub $2,%sp
mov %ax,10021
jmp _L8
_L7:
mov 10021,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10021
_L8:
mov 10019,%ax
push %ax
mov 10021,%ax
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
mov 10021,%ax
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
mov %ax,10023
mov %si,%ax
mov %ax,10025
mov %dx,%ax
mov %ax,10027
mov $0,%ax
sub $2,%sp
mov %ax,10029
mov $0,%ax
sub $2,%sp
mov %ax,10031
jmp _L11
_L10:
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
push %ax
mov 10025,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10029,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10029
_L11:
mov 10025,%ax
push %ax
mov 10029,%ax
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
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
push %ax
mov 10031,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
push %ax
mov 10031,%ax
pop %cx
add %cx,%ax
push %ax
mov 10027,%ax
push %ax
mov 10031,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10031,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10031
_L14:
mov 10027,%ax
push %ax
mov 10031,%ax
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
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
push %ax
mov 10031,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10023,%ax
push %ax
mov 10029,%ax
pop %cx
add %cx,%ax
push %ax
mov 10031,%ax
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
mov %ax,10033
mov %si,%ax
mov %ax,10035
mov $0,%ax
sub $2,%sp
mov %ax,10036
jmp _L17
_L16:
mov 10036,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10036
_L17:
mov 10033,%ax
push %ax
mov 10036,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
push %ax
mov 10035,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L18
mov $-1,%ax
_L18:
cmp $1, %ax
je _L16
mov 10033,%ax
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
memcpy:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10038
mov %si,%ax
mov %ax,10040
mov %dx,%ax
mov %ax,10042
mov $0,%ax
sub $2,%sp
mov %ax,10044
jmp _L20
_L19:
mov 10038,%ax
push %ax
mov 10044,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov 10038,%ax
push %ax
mov 10044,%ax
pop %cx
add %cx,%ax
push %ax
mov 10040,%ax
push %ax
mov 10044,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
pop %bx
mov %ax,0(%bx)
mov 10044,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10044
_L20:
mov 10044,%ax
push %ax
mov 10042,%ax
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
mov $111,%ax
mov %ax,10046
mov $108,%ax
mov %ax,10047
mov $100,%ax
mov %ax,10048
mov $0,%ax
mov %ax,10049
mov $10046,%ax
sub $2,%sp
mov %ax,10050
mov $110,%ax
mov %ax,10052
mov $101,%ax
mov %ax,10053
mov $119,%ax
mov %ax,10054
mov $0,%ax
mov %ax,10055
mov $10052,%ax
sub $2,%sp
mov %ax,10056
mov 10050,%ax
mov %ax,%di
mov 10056,%ax
mov %ax,%si
mov $3,%ax
mov %ax,%dx
call memcpy
mov 10050,%ax
mov %ax,%di
call puts
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
