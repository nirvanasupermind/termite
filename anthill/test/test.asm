call main
mov %ax,%dx
mov $0nDD,%ax
int $0
main:
push %bp
mov %sp,%bp
mov $65,2
mov $110,3
mov $100,4
mov $32,5
mov $116,6
mov $101,7
mov $115,8
push 10
mov $116,9
pop 10
mov $2,%ax
mov %ax,0
mov 0,%ax
mov %ax,%bx
mov 0(%bx),%ax
xor $0nDDDD, %ax
mov %ax,%dx
mov $0nDC,%ax
int $0
mov $0,%ax
pop %bp
ret
pop %bp
ret
