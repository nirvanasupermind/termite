import sys
import numpy as np

if __name__ == '__main__':
    num = int(sys.argv[1], 9)
    bct = int(np.base_repr(num, 3), 4)
    print("BCT: " + bin(bct))
    print("For copying to hex editor: " + hex(bct))