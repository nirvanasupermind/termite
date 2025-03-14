mov $3,%ax
push %ax
mov $4,%ax
pop %dx
and %dx,%ax
mov %ax,%dx
int 0nDC