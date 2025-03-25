call main
fac:
push %bp
mov %sp,%bp
mov %di,%ax
mov %ax,-2(%bp)
mov -2(%bp),%ax
mov -2(%bp),%ax
push %ax
mov -2(%bp),%ax
pop %cx
mul %cx
pop %bp
ret
pop %bp
ret
main:
push %bp
mov %sp,%bp
mov fac,%ax
mov $5,%ax
mov %ax,%di
call fac
mov %ax,2
mov 2,%ax
mov %ax,%dx
mov $0nDC,%ax
int 0
pop %bp
ret
