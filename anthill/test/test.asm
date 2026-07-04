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
ldt $ 0
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
ldt $ 10
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
abs:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10019
mov 10019,%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L9
mov $-1,%ax
_L9:
cmp $1, %ax
jne _L7
mov 10019,%ax
neg %ax
mov %bp,%sp
pop %bp
ret
jmp _L8
_L7:
mov 10019,%ax
mov %bp,%sp
pop %bp
ret
_L8:
mov %bp,%sp
pop %bp
ret
atoi:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10021
mov $0,%ax
sub $2,%sp
mov %ax,10023
mov $0,%ax
sub $2,%sp
mov %ax,10025
jmp _L11
_L10:
mov 10021,%ax
push %ax
mov 10023,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
sub $1,%sp
mov %ax,10027
mov 10027,%ax
push %ax
ldt $ 51
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L12
mov $-1,%ax
_L12:
mov %ax,%di
call puti
mov 10027,%ax
push %ax
ldt $ 48
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L15
mov $-1,%ax
_L15:
cmp $1, %ax
jne _L13
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
mov %ax,10025
jmp _L14
_L13:
_L14:
mov 10027,%ax
push %ax
ldt $ 49
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L18
mov $-1,%ax
_L18:
cmp $1, %ax
jne _L16
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L17
_L16:
_L17:
mov 10027,%ax
push %ax
ldt $ 50
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L21
mov $-1,%ax
_L21:
cmp $1, %ax
jne _L19
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L20
_L19:
_L20:
mov 10027,%ax
push %ax
ldt $ 51
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L24
mov $-1,%ax
_L24:
cmp $1, %ax
jne _L22
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $3,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L23
_L22:
_L23:
mov 10027,%ax
push %ax
ldt $ 52
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L27
mov $-1,%ax
_L27:
cmp $1, %ax
jne _L25
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $4,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L26
_L25:
_L26:
mov 10027,%ax
push %ax
ldt $ 53
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L30
mov $-1,%ax
_L30:
cmp $1, %ax
jne _L28
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $5,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L29
_L28:
_L29:
mov 10027,%ax
push %ax
ldt $ 54
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L33
mov $-1,%ax
_L33:
cmp $1, %ax
jne _L31
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $6,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L32
_L31:
_L32:
mov 10027,%ax
push %ax
ldt $ 55
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L36
mov $-1,%ax
_L36:
cmp $1, %ax
jne _L34
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $7,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L35
_L34:
_L35:
mov 10027,%ax
push %ax
ldt $ 56
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L39
mov $-1,%ax
_L39:
cmp $1, %ax
jne _L37
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $8,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L38
_L37:
_L38:
mov 10027,%ax
push %ax
ldt $ 57
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L42
mov $-1,%ax
_L42:
cmp $1, %ax
jne _L40
mov $10,%ax
push %ax
mov 10025,%ax
pop %cx
mul %cx
push %ax
mov $9,%ax
pop %cx
add %cx,%ax
mov %ax,10025
jmp _L41
_L40:
_L41:
mov 10023,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10023
_L11:
mov 10021,%ax
push %ax
mov 10023,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $ 0
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L43
mov $-1,%ax
_L43:
cmp $1, %ax
je _L10
mov 10023,%ax
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
ldt $ 51
push %ax
ldt $ 50
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L44
mov $-1,%ax
_L44:
mov %ax,%di
call puti
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
