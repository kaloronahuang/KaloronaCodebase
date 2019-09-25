# P3223.py
import math

def A(x, y):
    return math.factorial(x) // math.factorial(x - y)

ans = 0
n, m = map(int, input().split())

if n + 1 >= 2 and n + 3 >= m:
    ans += math.factorial(n) * A(n + 1, 2) * A(n + 3, m)

if n + 2 >= m - 1 and m >= 1:
    ans += math.factorial(n) * (n + 1) * 2 * m * A(n + 2, m - 1)

print(int(ans))