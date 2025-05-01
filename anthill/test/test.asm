call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $4,%ax
mov %ax,-0(%bp)
mov -0(%bp),%ax
mov $-0,%ax
add %bp,%ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
