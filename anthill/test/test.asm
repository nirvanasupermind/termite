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
mov %ax,-2(%bp)
jmp _L2
_L1:
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov -2(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov %ax,%di
call print_char
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,-2(%bp)
_L2:
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov -2(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
xor $0nDDDD, %ax
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov -2(%bp),%ax
pop %cx
add %cx,%ax
mov 0(%ax),%ax
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
mov $72,-0(%bp)
mov $101,-1(%bp)
mov $108,-2(%bp)
mov $108,-3(%bp)
mov $111,-4(%bp)
mov $32,-5(%bp)
mov $119,-6(%bp)
mov $111,-7(%bp)
mov $114,-8(%bp)
mov $108,-9(%bp)
mov $100,-10(%bp)
mov $33,-11(%bp)
push -11(%bp)
mov $0,-12(%bp)
pop -11(%bp)
mov $-0(%bp),%ax
mov %ax,-13(%bp)
mov -13(%bp),%ax
mov %ax,%di
call print_int
mov $0,%ax
pop %bp
ret
pop %bp
ret
