call main
sqrt:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10000
mov 10000,%ax
fld %ax
fsqrt
fstp %ax
mov %bp,%sp
pop %bp
ret
sin:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10004
mov 10004,%ax
mov %bp,%sp
pop %bp
ret
cos:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10008
mov 10008,%ax
fld %ax
fcos
fstp %ax
mov %bp,%sp
pop %bp
ret
tan:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10012
mov 10012,%ax
fld %ax
ftan
fstp %ax
mov %bp,%sp
pop %bp
ret
atan2:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10016
mov %si,%ax
mov %ax,10020
mov 10016,%ax
fld %ax
mov 10020,%ax
fld %ax
fatan
fstp %ax
mov %bp,%sp
pop %bp
ret
exp:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10024
mov 10024,%ax
fld %ax
fexp
fstp %ax
mov %bp,%sp
pop %bp
ret
log:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10028
mov 10028,%ax
fld %ax
flog
fstp %ax
mov %bp,%sp
pop %bp
ret
pow:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10032
mov %si,%ax
mov %ax,10036
mov 10036,%ax
fld %ax
mov 10032,%ax
mov %ax,%di
call log
fld %ax
fmul
fstp %ax
mov %ax,%di
call exp
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
abs:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10040
mov 10040,%ax
fld %ax
fabs
fstp %ax
mov %bp,%sp
pop %bp
ret
floor:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10044
mov 10044,%ax
fld %ax
ffloor
fstp %ax
mov %bp,%sp
pop %bp
ret
hypot:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10048
mov %si,%ax
mov %ax,10052
mov 10048,%ax
fld %ax
mov 10048,%ax
fld %ax
fmul
fstp %ax
fld %ax
mov 10052,%ax
fld %ax
mov 10052,%ax
fld %ax
fmul
fstp %ax
fld %ax
fadd
fstp %ax
mov %ax,%di
call sqrt
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
putc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10056
mov 10056,%ax
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
mov %ax,10058
mov 10058,%ax
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
mov %ax,10060
mov 10060,%ax
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
mov %ax,10064
mov $0,%ax
sub $2,%sp
mov %ax,10066
jmp _L2
_L1:
mov 10064,%ax
push %ax
mov 10066,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov %ax,%di
call putc
mov 10066,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10066
_L2:
mov 10064,%ax
push %ax
mov 10066,%ax
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
mov %ax,10068
mov $1,%ax
sub $2,%sp
mov %ax,10070
mov $1,%ax
sub $2,%sp
mov %ax,10072
jmp _L5
_L4:
mov 10072,%ax
push %ax
mov 10070,%ax
pop %cx
mul %cx
mov %ax,10072
mov 10070,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10070
_L5:
mov 10070,%ax
push %ax
mov 10068,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jle _L6
mov $-1,%ax
_L6:
cmp $1, %ax
je _L4
mov 10072,%ax
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
mov $10074,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
mov %ax,%di
mov $10078,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
mov %ax,%si
call hypot
mov %ax,%di
call puti
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
