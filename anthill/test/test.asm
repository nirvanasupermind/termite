mov $30,%ax
mov %ax,0
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov 0,%ax
mov 0,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
