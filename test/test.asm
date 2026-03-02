mov $0n13000000, 0
mov $1, 2
mov $0,%ax
fld %ax
mov $0nCA, %ax
int $0
mov $0nDD, %ax
int $0