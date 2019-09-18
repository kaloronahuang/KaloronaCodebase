// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100010, INF = 0x3f3f3f3f;

int n, m, q, mem[MAX_N], siz[MAX_N], tim[MAX_N], fa[MAX_N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y, int ti)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (siz[x] < siz[y])
        swap(x, y);
    siz[x] += siz[y], tim[y] = ti;
    mem[y] = x;
    fa[y] = x;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        mem[i] = i, siz[i] = 1, tim[i] = INF, fa[i] = i;
    for (int day = 1; day <= m; day++)
    {
        int gcd = (m - day + 1);
        for (int i = gcd + gcd; i <= n; i += gcd)
            merge(i, i - gcd, day);
    }
    while (q--)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int ans = 0;
        while (x != y)
        {
            if (tim[x] < tim[y] && tim[x] != INF)
            {
                ans = max(tim[x], ans), x = mem[x];
                continue;
            }
            if (tim[x] > tim[y] && tim[y] != INF)
            {
                ans = max(tim[y], ans), y = mem[y];
                continue;
            }
            if (tim[x] == tim[y] && tim[x] != INF)
            {
                ans = max(ans, max(tim[x], tim[y]));
                x = mem[x], y = mem[y];
                continue;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}