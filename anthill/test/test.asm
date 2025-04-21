call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $50,%ax
mov %ax,0
mov 0,%ax
mov $0,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
