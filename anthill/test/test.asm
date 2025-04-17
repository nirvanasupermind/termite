call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $5,%ax
mov %ax,2
mov $900,%ax
mov %ax,4
mov $4,%ax
mov %ax,6
mov 6,%ax
mov %ax,%dx
mov 0(%dx),%ax
neg %ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
