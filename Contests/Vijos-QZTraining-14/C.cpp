// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30010;

int fa[MAX_N], siz[MAX_N], beneath[MAX_N];
char opt[3];

int find(int x)
{
    if (x == fa[x])
        return x;
    int up = fa[x];
    fa[x] = find(fa[x]);
    beneath[x] += beneath[up];
    return fa[x];
}

int main()
{
    for (int i = 0; i < MAX_N; i++)
        fa[i] = i, siz[i] = 1;
    int m;
    scanf("%d", &m);
    while (m--)
    {
        scanf("%s", opt + 1);
        int a, b;
        if (opt[1] == 'M')
        {
            scanf("%d%d", &a, &b);
            int f_a = find(a), f_b = find(b);
            beneath[f_a] = siz[f_b];
            siz[f_b] += siz[f_a];
            siz[f_a] = 0;
            fa[f_a] = f_b;
        }
        else
            scanf("%d", &a), find(a), printf("%d\n", beneath[a]);
    }
    return 0;
}