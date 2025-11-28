call main
z:
push %ax
ret
main:
mov $123, %ax
call z
pop %ax
mov $0nDD, %ax
int $0