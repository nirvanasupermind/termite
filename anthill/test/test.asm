call main
mov $0,%dx
mov $0nDD,%ax
int $0
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
fld %ax
fsin
fstp %ax
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
log3:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10032
mov 10032,%ax
mov %ax,%di
call log
fld %ax
mov $10036,%ax
mov $4782969,0(%ax)
mov $1,2(%ax)
mov %ax,%di
call log
fld %ax
fdiv
fstp %ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
pow:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10040
mov %si,%ax
mov %ax,10044
mov 10044,%ax
fld %ax
mov 10040,%ax
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
floor:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10048
mov 10048,%ax
fld %ax
ffloor
fstp %ax
mov %bp,%sp
pop %bp
ret
round:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10052
mov 10052,%ax
fld %ax
mov $10056,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
fadd
fstp %ax
mov %ax,%di
call floor
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
hypot:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10060
mov %si,%ax
mov %ax,10064
mov 10060,%ax
fld %ax
mov 10060,%ax
fld %ax
fmul
fstp %ax
fld %ax
mov 10064,%ax
fld %ax
mov 10064,%ax
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
f_abs:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10068
mov 10068,%ax
fld %ax
fabs
fstp %ax
mov %bp,%sp
pop %bp
ret
fmin:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10072
mov %si,%ax
mov %ax,10076
mov 10072,%ax
fld %ax
mov 10076,%ax
fld %ax
fcmp
mov $1,%ax
jl _L3
mov $-1,%ax
_L3:
cmp $1, %ax
jne _L1
mov 10072,%ax
mov %bp,%sp
pop %bp
ret
jmp _L2
_L1:
mov 10076,%ax
mov %bp,%sp
pop %bp
ret
_L2:
mov %bp,%sp
pop %bp
ret
fmax:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10080
mov %si,%ax
mov %ax,10084
mov 10080,%ax
fld %ax
mov 10084,%ax
fld %ax
fcmp
mov $1,%ax
jg _L6
mov $-1,%ax
_L6:
cmp $1, %ax
jne _L4
mov 10080,%ax
mov %bp,%sp
pop %bp
ret
jmp _L5
_L4:
mov 10084,%ax
mov %bp,%sp
pop %bp
ret
_L5:
mov %bp,%sp
pop %bp
ret
putc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10088
mov 10088,%ax
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
mov %ax,10090
mov 10090,%ax
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
mov %ax,10092
mov 10092,%ax
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
mov %ax,10096
mov $0,%ax
sub $2,%sp
mov %ax,10098
jmp _L8
_L7:
mov 10096,%ax
push %ax
mov 10098,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
mov %ax,%di
call putc
mov 10098,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,10098
_L8:
mov 10096,%ax
push %ax
mov 10098,%ax
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
mov %bp,%sp
pop %bp
ret
fact:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10100
mov $1,%ax
sub $2,%sp
mov %ax,10102
mov $1,%ax
sub $2,%sp
mov %ax,10104
jmp _L11
_L10:
mov 10104,%ax
push %ax
mov 10102,%ax
pop %cx
mul %cx
mov %ax,10104
mov 10102,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10102
_L11:
mov 10102,%ax
push %ax
mov 10100,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jle _L12
mov $-1,%ax
_L12:
cmp $1, %ax
je _L10
mov 10104,%ax
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
mov $10106,%ax
mov $7174454,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10110,%ax
mov $7174454,0(%ax)
mov $0,2(%ax)
fld %ax
fmul
fstp %ax
mov %ax,%di
call putf
mov $0,%ax
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
