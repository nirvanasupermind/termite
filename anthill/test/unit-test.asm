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
test_char_lit:
push %bp
mov %sp,%bp
mov $99,%ax
mov %ax,%di
call print_char
mov $104,%ax
mov %ax,%di
call print_char
mov $97,%ax
mov %ax,%di
call print_char
mov $114,%ax
mov %ax,%di
call print_char
mov $95,%ax
mov %ax,%di
call print_char
mov $108,%ax
mov %ax,%di
call print_char
mov $105,%ax
mov %ax,%di
call print_char
mov $116,%ax
mov %ax,%di
call print_char
mov $32,%ax
mov %ax,%di
call print_char
mov $65,%ax
mov $65,%ax
push %ax
mov $65,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
je _L1
mov $0,%ax
_L1:
xor $0nDDD4, %ax
mov %ax,%di
call print_int
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
call test_char_lit
mov $0,%ax
pop %bp
ret
pop %bp
ret
