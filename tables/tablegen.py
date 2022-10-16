# -*- tablegen.py -*-
# Part of the Termite project, under the MIT License.

# This Python script generates lookup tables used in the tables.hpp file.

def ter(n):
    if n == 0:
        return [0, 0, 0]
    nums = []
    for i in range(0, 3):
        n, r = divmod(n, 3)
        nums.append(r)

    return nums

def bct_str(nums):
    t = ['00' if r == 0 else ('01' if r == 1 else '10') for r in nums]
    t.reverse()
    return '0b' + '\''.join(t)

def tritwise_and(a, b):
    return [min(x, y) for x, y in zip(a, b)]

def tritwise_or(a, b):
    return [max(x, y) for x, y in zip(a, b)]

def tritwise_xor(a, b):
    return [((x + y) % 3) for x, y in zip(a, b)]

def create_tritwise_table(fn):
    table = '\t{\n'

    for i in range(0, 27):
        if i:
            table += '\n'

        table += f'\t\t{{{bct_str(ter(i))}, std::map<char, char>{{'

        for j in range(0, 27):
            table += f'\n\t\t\t{{{bct_str(ter(j))}, {bct_str(fn(ter(i), ter(j)))}}}'

            if j != 26:
                table += ','

        if i == 26:
            table += '\n\t\t}}\n\t};'
        else:
            table += '\n\t\t}},'

    return table

if __name__ == '__main__':                
    tritwise_and_table = create_tritwise_table(tritwise_and)
    tritwise_or_table = create_tritwise_table(tritwise_or)
    tritwise_xor_table = create_tritwise_table(tritwise_xor)

    open('tables/tritwise_and_table.txt', 'w').write(tritwise_and_table)
    open('tables/tritwise_or_table.txt', 'w').write(tritwise_or_table)
    open('tables/tritwise_xor_table.txt', 'w').write(tritwise_xor_table)