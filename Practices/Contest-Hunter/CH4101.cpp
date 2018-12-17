// CH4101.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 30020;
int mem[maxn], d[maxn], siz[maxn], T;
int find(int x)
{
    if (x == mem[x])
        return x;
    int fat = find(mem[x]);
    d[x] += d[mem[x]];
    return mem[x] = fat;
}
void merge(int x, int y)
{
    int rx = find(x), ry = find(y);
    if (rx != ry)
    {
        mem[ry] = rx;
        d[ry] = siz[rx];
        siz[rx] += siz[ry];
    }
}
int main()
{
    fill(siz, siz + maxn, 1);
    for (int i = 0; i < maxn; i++)
        mem[i] = i;
    scanf("%d", &T);
    while (T--)
    {
        char opt;
        int i, j;
        cin >> opt >> i >> j;
        if (opt == 'M')
            merge(j, i);
        else if (find(i) != find(j))
            printf("-1\n");
        else
            printf("%d\n", abs(d[i] - d[j]) - 1);
    }
    return 0;
}