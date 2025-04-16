call main
f:
push %bp
mov %sp,%bp
mov $5,%ax
pop %bp
ret
main:
push %bp
mov %sp,%bp
call f
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret