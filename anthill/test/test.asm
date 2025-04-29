call main
mov %ax,%dx
mov $0nDD,%ax
int $0
print_char:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-0(%bp)
mov -0(%bp),%ax
mov %ax,%dx
mov $0nD0,%ax
int $0
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
print_int:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-0(%bp)
mov -0(%bp),%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
print_str:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-0(%bp)
mov $0,%ax
mov %ax,0
jmp _L2
_L1:
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov 0,%ax
pop %cx
add %cx,%ax
mov %ax,%bx
mov 0(%bx),%ax
xor $0nDDDD, %ax
mov %ax,%di
call print_char
mov 0,%ax
mov 0,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,0
_L2:
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov 0,%ax
pop %cx
add %cx,%ax
mov %ax,%bx
mov 0(%bx),%ax
xor $0nDDDD, %ax
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov 0,%ax
pop %cx
add %cx,%ax
mov %ax,%bx
mov 0(%bx),%ax
xor $0nDDDD, %ax
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
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $104,0
mov $101,1
mov $108,2
mov $108,3
mov $111,4
push 6
mov $0,5
pop 6
mov $0,%ax
mov %ax,6
mov $0,%ax
mov %ax,8
jmp _L2
_L1:
mov 6,%ax
mov 6,%ax
push %ax
mov 8,%ax
pop %cx
add %cx,%ax
mov %ax,%bx
mov 0(%bx),%ax
xor $0nDDDD, %ax
mov %ax,%di
call print_char
mov 8,%ax
mov 8,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,8
_L2:
mov 8,%ax
mov 8,%ax
push %ax
mov $20,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jl _L3
mov $-1,%ax
_L3:
cmp $1, %ax
je _L1
mov $0,%ax
pop %bp
ret
pop %bp
ret
