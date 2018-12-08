# AtCoder Beginner Contest 115 - D.py
anss = [0, 0, 0, 1, 2, 3, 3]
lenarr = [0,6]
phitab = [0,3]

def phi(i):
    return phitab[i]


def getlen(i):
    return lenarr[i]


def f(x, n):
    if n == 1:
        return anss[x]
    if x > getlen(n)/2:
        return phi(n) - f(getlen(n)-x+1, n)
    else:
        return f(x-1, n-1)

for i in range(2,60):
    lenarr.append(2*lenarr[i-1]+2)
for i in range(2,60):
    phitab.append(2*phitab[i-1]+1)
arg = input()
N = int(arg.split()[0])
X = int(arg.split()[1])
print(f(X+1, N))