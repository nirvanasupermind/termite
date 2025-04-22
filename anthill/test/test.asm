call main
mov %ax,%dx
mov $0nDD,%ax
int $0
mov $0, 0
mov $1, 2
mov $2, 4
mov $3, 6
main:
push %bp
mov %sp,%bp
mov 6,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
