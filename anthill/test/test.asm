mov $14,%ax
mov %ax,0
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
f:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-0(%bp)
mov -0(%bp),%ax
mov -0(%bp),%ax
push %ax
mov -0(%bp),%ax
pop %cx
mul %cx
pop %bp
ret
pop %bp
ret
call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $5,%ax
mov %ax,%di
call f
mov %ax,2
mov 2,%ax
mov 2,%ax
push %ax
mov 0,%ax
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
