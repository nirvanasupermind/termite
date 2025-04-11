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
mov $0,%ax
pop %bp
ret