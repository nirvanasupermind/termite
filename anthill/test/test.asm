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
sqrt:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10019
mov 10019,%ax
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
mov %ax,10023
mov 10023,%ax
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
mov %ax,10027
mov 10027,%ax
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
mov %ax,10031
mov 10031,%ax
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
mov %ax,10035
mov %si,%ax
mov %ax,10039
mov 10035,%ax
fld %ax
mov 10039,%ax
fld %ax
fatan
fstp %ax
mov %bp,%sp
pop %bp
ret
atan:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10043
mov 10043,%ax
mov %ax,%di
mov $10047,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
mov %ax,%si
call atan2
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
asin:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10051
mov 10051,%ax
mov %ax,%di
mov $10055,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
mov 10051,%ax
fld %ax
mov 10051,%ax
fld %ax
fmul
fstp %ax
fld %ax
fsub
fstp %ax
mov %ax,%di
call sqrt
mov %ax,%si
call atan2
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
acos:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10059
mov $10063,%ax
mov $7513070,0(%ax)
mov $0,2(%ax)
fld %ax
mov 10059,%ax
mov %ax,%di
call asin
fld %ax
fsub
fstp %ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
exp:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10067
mov 10067,%ax
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
mov %ax,10071
mov 10071,%ax
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
mov %ax,10075
mov 10075,%ax
mov %ax,%di
call log
fld %ax
mov $10079,%ax
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
log10:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10083
mov 10083,%ax
mov %ax,%di
call log
fld %ax
mov $10087,%ax
mov $5314410,0(%ax)
mov $2,2(%ax)
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
mov %ax,10091
mov %si,%ax
mov %ax,10095
mov 10095,%ax
fld %ax
mov 10091,%ax
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
mov %ax,10099
mov 10099,%ax
fld %ax
ffloor
fstp %ax
mov %bp,%sp
pop %bp
ret
ceil:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10103
mov 10103,%ax
fld %ax
fneg
fstp %ax
mov %ax,%di
call floor
fld %ax
fneg
fstp %ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
round:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10107
mov 10107,%ax
fld %ax
mov $10111,%ax
mov $7174454,0(%ax)
mov $-1,2(%ax)
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
trunc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10115
mov 10115,%ax
fld %ax
mov $10119,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fcmp
jl _L9
mov $1,%ax
_L9:
mov $-1,%ax
_L10:
cmp $1, %ax
jne _L7
mov 10115,%ax
fld %ax
fneg
fstp %ax
mov %ax,%di
call floor
fld %ax
fneg
fstp %ax
mov %bp,%sp
pop %bp
ret
jmp _L8
_L7:
mov 10115,%ax
mov %ax,%di
call floor
mov %bp,%sp
pop %bp
ret
_L8:
mov %bp,%sp
pop %bp
ret
hypot:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10123
mov %si,%ax
mov %ax,10127
mov 10123,%ax
fld %ax
mov 10123,%ax
fld %ax
fmul
fstp %ax
fld %ax
mov 10127,%ax
fld %ax
mov 10127,%ax
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
mov %ax,10131
mov 10131,%ax
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
mov %ax,10135
mov %si,%ax
mov %ax,10139
mov 10135,%ax
fld %ax
mov 10139,%ax
fld %ax
fcmp
jl _L13
mov $1,%ax
_L13:
mov $-1,%ax
_L14:
cmp $1, %ax
jne _L11
mov 10135,%ax
mov %bp,%sp
pop %bp
ret
jmp _L12
_L11:
mov 10139,%ax
mov %bp,%sp
pop %bp
ret
_L12:
mov %bp,%sp
pop %bp
ret
fmax:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10143
mov %si,%ax
mov %ax,10147
mov 10143,%ax
fld %ax
mov 10147,%ax
fld %ax
fcmp
mov $1,%ax
jg _L17
mov $-1,%ax
_L17:
cmp $1, %ax
jne _L15
mov 10143,%ax
mov %bp,%sp
pop %bp
ret
jmp _L16
_L15:
mov 10147,%ax
mov %bp,%sp
pop %bp
ret
_L16:
mov %bp,%sp
pop %bp
ret
isfinite:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10151
mov 10151,%ax
fld %ax
mov $10155,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10159,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fdiv
fstp %ax
fld %ax
fcmp
jne _L18
mov $-1,%ax
_L18:
push %ax
mov 10151,%ax
fld %ax
mov $10163,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10167,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fdiv
fstp %ax
fld %ax
fneg
fstp %ax
fld %ax
fcmp
jne _L19
mov $-1,%ax
_L19:
pop %cx
and %cx,%ax
push %ax
mov 10151,%ax
fld %ax
mov $10171,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10175,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fdiv
fstp %ax
fld %ax
fcmp
jne _L20
mov $-1,%ax
_L20:
pop %cx
and %cx,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
isinf:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10179
mov 10179,%ax
fld %ax
mov $10183,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10187,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fdiv
fstp %ax
fld %ax
fcmp
mov $1,%ax
je _L21
mov $-1,%ax
_L21:
push %ax
mov 10179,%ax
fld %ax
mov $10191,%ax
mov $4782969,0(%ax)
mov $0,2(%ax)
fld %ax
mov $10195,%ax
mov $0,0(%ax)
mov $0,2(%ax)
fld %ax
fdiv
fstp %ax
fld %ax
fneg
fstp %ax
fld %ax
fcmp
mov $1,%ax
je _L22
mov $-1,%ax
_L22:
pop %cx
or %cx,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
isnan:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10199
mov 10199,%ax
sub $2,%sp
mov %ax,10203
mov 10203,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
sub $2,%sp
mov %ax,10205
mov 10205,%ax
push %ax
mov $21523360,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L23
mov $-1,%ax
_L23:
push %ax
mov 10199,%ax
mov %ax,%di
call isinf
neg %ax
pop %cx
and %cx,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
mov $1,%ax
mov %ax,10207
calloc:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10209
mov %si,%ax
mov %ax,10211
ldt $0
sub $1,%sp
mov %ax,10213
mov 10213,%ax
mov $10213,%ax
sub $2,%sp
mov %ax,10214
mov $1,%ax
sub $2,%sp
mov %ax,10216
jmp _L25
_L24:
mov 10214,%ax
push %ax
mov 10216,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
mov 10214,%ax
push %ax
mov 10216,%ax
pop %cx
add %cx,%ax
push %ax
mov $0,%ax
pop %bx
mov %ax,0(%bx)
mov 10216,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10216
_L25:
mov 10216,%ax
push %ax
mov 10209,%ax
push %ax
mov 10211,%ax
pop %cx
mul %cx
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L26
mov $-1,%ax
_L26:
cmp $1, %ax
je _L24
mov 10214,%ax
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
mov %ax,10218
mov 10218,%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L29
mov $-1,%ax
_L29:
cmp $1, %ax
jne _L27
mov 10218,%ax
neg %ax
mov %bp,%sp
pop %bp
ret
jmp _L28
_L27:
mov 10218,%ax
mov %bp,%sp
pop %bp
ret
_L28:
mov %bp,%sp
pop %bp
ret
atoi:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10220
mov 10220,%ax
ldt 0(%ax)
push %ax
ldt $45
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L32
mov $-1,%ax
_L32:
cmp $1, %ax
jne _L30
mov 10220,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,%di
call atoi
neg %ax
mov %bp,%sp
pop %bp
ret
jmp _L31
_L30:
_L31:
mov $0,%ax
sub $2,%sp
mov %ax,10222
mov $0,%ax
sub $2,%sp
mov %ax,10224
jmp _L34
_L33:
mov 10220,%ax
push %ax
mov 10222,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
sub $1,%sp
mov %ax,10226
mov $10,%ax
push %ax
mov 10224,%ax
pop %cx
mul %cx
push %ax
mov 10226,%ax
push %ax
ldt $48
pop %cx
xchg %cx,%ax
sub %cx,%ax
xor $0nDDDD, %ax
pop %cx
add %cx,%ax
mov %ax,10224
mov 10222,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10222
_L34:
mov 10220,%ax
push %ax
mov 10222,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $0
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L35
mov $-1,%ax
_L35:
cmp $1, %ax
je _L33
mov 10224,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
atof:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10227
mov $0,%ax
sub $2,%sp
mov %ax,10229
mov $0,%ax
sub $2,%sp
mov %ax,10231
mov 10227,%ax
push %ax
mov 10229,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $45
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L38
mov $-1,%ax
_L38:
cmp $1, %ax
jne _L36
mov $1,%ax
mov %ax,10231
mov 10229,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10229
jmp _L37
_L36:
_L37:
mov $0,%ax
sub $2,%sp
mov %ax,10233
mov $0,%ax
sub $2,%sp
mov %ax,10235
mov $0,%ax
sub $2,%sp
mov %ax,10237
jmp _L40
_L39:
mov 10227,%ax
push %ax
mov 10229,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $46
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L43
mov $-1,%ax
_L43:
cmp $1, %ax
jne _L41
mov $1,%ax
mov %ax,10237
jmp _L42
_L41:
mov 10227,%ax
push %ax
mov 10229,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $48
pop %cx
xchg %cx,%ax
sub %cx,%ax
xor $0nDDDD, %ax
sub $2,%sp
mov %ax,10239
mov 10233,%ax
push %ax
mov $10,%ax
pop %cx
mul %cx
push %ax
mov 10239,%ax
pop %cx
add %cx,%ax
mov %ax,10233
mov 10237,%ax
cmp $1, %ax
jne _L44
mov 10235,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10235
jmp _L45
_L44:
_L45:
_L42:
mov 10229,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,10229
_L40:
mov 10227,%ax
push %ax
mov 10229,%ax
pop %cx
add %cx,%ax
ldt 0(%ax)
push %ax
ldt $0
pop %cx
cmp %ax,%cx
mov $1,%ax
jne _L46
mov $-1,%ax
_L46:
cmp $1, %ax
je _L39
mov 10233,%ax
mov %ax,9990
fild $9990
mov $10241,%ax
fstp %ax
sub $4,%sp
mov %ax,10245
jmp _L48
_L47:
mov 10245,%ax
fld %ax
mov $10249,%ax
mov $5314410,0(%ax)
mov $2,2(%ax)
fld %ax
fdiv
fstp %ax
mov %ax,10245
mov 10235,%ax
push %ax
mov $1,%ax
pop %cx
xchg %cx,%ax
sub %cx,%ax
mov %ax,10235
_L48:
mov 10235,%ax
push %ax
mov $0,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jg _L49
mov $-1,%ax
_L49:
cmp $1, %ax
je _L47
mov 10231,%ax
cmp $1, %ax
jne _L50
mov 10245,%ax
fld %ax
fneg
fstp %ax
mov %ax,10245
jmp _L51
_L50:
_L51:
mov 10245,%ax
mov %bp,%sp
pop %bp
ret
mov %bp,%sp
pop %bp
ret
exit:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10253
mov %ax,%dx
mov $0nDD,%ax
int $0
mov %bp,%sp
pop %bp
ret
srand:
push %bp
mov %sp,%bp
sub $729,%sp
mov %di,%ax
mov %ax,10255
mov 10255,%ax
mov %ax,10207
mov %bp,%sp
pop %bp
ret
rand:
push %bp
mov %sp,%bp
sub $729,%sp
mov $1664524,%ax
push %ax
mov 10207,%ax
pop %cx
mul %cx
push %ax
mov $23829640,%ax
pop %cx
add %cx,%ax
mov %ax,10207
mov 10207,%ax
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
mov $10257,%ax
mov $5325629,0(%ax)
mov $4,2(%ax)
fld %ax
fneg
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
