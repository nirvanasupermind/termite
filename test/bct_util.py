import sys

def ternary (n):
    if n == 0:
        return '0'
    nums = []
    while n:
        n, r = divmod(n, 3)
        nums.append(str(r))
    return ''.join(reversed(nums))

def bct(n):
    return hex(int(ternary(n), 4))

if __name__ == '__main__':
    print(bct(int(sys.argv[1])))