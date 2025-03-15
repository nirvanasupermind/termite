mov $2,%ax
mov $2,%ax
push %ax
mov $3,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne 3
mov $0,%ax
label3:
cmp $1, %ax
jne label1
mov $4,%ax
mov $2,%ax
mov $2,%ax
push %ax
mov $3,%ax
pop %cx
cmp %ax,%cx
mov $1,%ax
jne 4
mov $0,%ax
label4:
cmp $1, %ax
je label2
label1:
mov $5,%ax
label2:
mov %ax,%dx
mov $0nDC, %ax
int 0