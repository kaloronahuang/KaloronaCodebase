# P1655.py
MAX_N = 405
stiring = [[0]*MAX_N for i in range(MAX_N)]
for i in range(1, MAX_N):
    stiring[i][i] = stiring[i][1] = 1
    for j in range(2, i):
        stiring[i][j] = stiring[i - 1][j - 1] + j * stiring[i - 1][j]
while True:
    try:
        n, m = map(int, input().split())
        print(stiring[n][m])
    except EOFError:
        break
