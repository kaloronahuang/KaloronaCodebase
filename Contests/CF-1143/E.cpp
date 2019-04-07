// E.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 200;
int perm[MAX_N], pos[MAX_N];
int arr[MAX_N], pre[MAX_N], n, m, q, fa[20][MAX_N], g[20][MAX_N], lg[MAX_N];
int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &perm[i]), pos[perm[i]] = i;
    perm[0] = perm[n];
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &arr[i]);
        int x = perm[pos[arr[i]] - 1];
        fa[0][i] = pre[x], pre[arr[i]] = i;
    }
    for (int i = 1; (1 << i) <= m; i++)
        for (int j = 1; j <= m; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= m; i++)
    {
        int l = n - 1, p = i;
        for (int j = 19; j >= 0; j--)
            if (l & (1 << j))
                p = fa[j][p];
        g[0][i] = p;
    }
    for (int i = 2; i <= m; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; (1 << i) <= m; i++)
        for (int j = 1; j + (1 << i) - 1 <= m; j++)
            g[i][j] = max(g[i - 1][j], g[i - 1][j + (1 << (i - 1))]);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int k = lg[r - l + 1];
        int ans = max(g[k][l], g[k][r - (1 << k) + 1]);
        if (ans >= l)
            putchar('1');
        else
            putchar('0');
    }
    return 0;
}