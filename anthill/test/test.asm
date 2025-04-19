call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $50000,%ax
mov $50000,%ax
mov %ax,2
mov 2,%ax
mov $2,%ax
mov %ax,%bx
mov 0(%bx),%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
