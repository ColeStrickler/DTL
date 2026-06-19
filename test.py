outfile = "./test.out"
lines = 1000
line = 0



col_offsets = [4,8,12];

def write(addr, f):
    global line
    global lines
    if line == lines:
        exit(0)
    f.write(tohex(addr))  # #x includes '0x' prefixq
    line += 1



def tohex(addr):
    return f"{addr:#x}\n"



def truncate_28(x: int) -> int:
    return x & ((1 << 28) - 1)


def isEdge(a, abound):
    return a == 0 or a == abound-1



height = 128
width = 128


def pad(dim, dk, dmax):
    return (dim + dk - 1) < 0 or (dim + dk - 1) >= dmax

offset = [18,37,50,2,54,31,24,48]
with open(outfile, "w") as f:
    for j  in range (0,8):
        for i in range (0, 500000):
            write((i*64+offset[j])*8, f)