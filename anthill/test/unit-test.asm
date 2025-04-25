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
mov $0,%ax
_L3:
cmp $1, %ax
je _L1
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
test_cast:
push %bp
mov %sp,%bp
mov $99,%ax
mov %ax,%di
call print_char
mov $97,%ax
mov %ax,%di
call print_char
mov $115,%ax
mov %ax,%di
call print_char
mov $116,%ax
mov %ax,%di
call print_char
mov $58,%ax
mov %ax,%di
call print_char
mov $32,%ax
mov %ax,%di
call print_char
mov $86438,%ax
xor $0nDDDD, %ax
mov %ax,%di
call print_int
mov $10,%ax
mov %ax,%di
call print_char
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
test_inc:
push %bp
mov %sp,%bp
mov $105,%ax
mov %ax,%di
call print_char
mov $110,%ax
mov %ax,%di
call print_char
mov $99,%ax
mov %ax,%di
call print_char
mov $58,%ax
mov %ax,%di
call print_char
mov $32,%ax
mov %ax,%di
call print_char
mov $57,%ax
mov %ax,2
mov 2,%ax
mov 2,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,2
mov 2,%ax
mov 2,%ax
push %ax
mov $58,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L4
mov $0,%ax
_L4:
mov %ax,%di
call print_int
mov $10,%ax
mov %ax,%di
call print_char
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
call test_cast
call test_inc
mov $0,%ax
pop %bp
ret
pop %bp
ret
