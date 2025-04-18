call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $13,%ax
mov $13,%ax
push %ax
mov $1,%ax
pop %cx
add %cx,%ax
mov %ax,2
mov 2,%ax
mov $2,%ax
mov %ax,4
mov 4,%bx
mov $104,%ax
mov $104,%ax
push %ax
mov $2,%ax
pop %cx
add %cx,%ax
mov %ax,0(%bx)
mov 4,%ax
mov %ax,%bx
mov 0(%bx),%ax
mov 2,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
