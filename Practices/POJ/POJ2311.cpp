// POJ2311.cpp
#include <cstdio>
#include <cstring>
const int MAX_N = 220;

int n, m, sg[MAX_N][MAX_N];

int process(int x, int y)
{
    if (sg[x][y] != -1)
        return sg[x][y];
    bool f[MAX_N];
    memset(f, 0, sizeof(f));
    for (int i = 2; i <= x - i; i++)
        f[process(i, y) ^ process(x - i, y)] = 1;

    for (int i = 2; i <= y - i; i++)
        f[process(x, i) ^ process(x, y - i)] = 1;
    int t = 0;
    // doing the mex;
    while (f[t])
        t++;
    return sg[x][y] = t;
}

int main()
{
    memset(sg, -1, sizeof(sg)), sg[2][3] = sg[2][2] = sg[3][2] = 0;
    while (scanf("%d%d", &n, &m) != EOF)
        puts(process(n, m) ? "WIN" : "LOSE");
    return 0;
}