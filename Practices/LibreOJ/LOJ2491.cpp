// LOJ2491.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int head[MAX_N], current, table[MAX_N][60], n, m, dep[MAX_N], fa[21][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dep[edges[i].to] = dep[u] + 1, fa[0][edges[i].to] = u, dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 20; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dep[1] = 1, dfs(1, 0);
    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= 50; k++)
            table[i][k] = 1LL * max(table[i][k - 1], 1) * i % mod;
    for (int k = 1; k <= 50; k++)
        for (int i = 1; i <= n; i++)
            table[i][k] = (1LL * table[i][k] + 1LL * table[i - 1][k]) % mod;
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    scanf("%d", &m);
    while (m--)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        int lca = getLCA(u, v);
        if (lca == u || lca == v)
        {
            if (lca == v)
                swap(u, v);
            // lca - v;
            long long tmp = table[dep[v] - 1][k] - table[max(dep[lca] - 2, 0)][k];
            if (tmp < 0)
                tmp += mod;
            tmp %= mod;
            printf("%lld\n", tmp);
        }
        else
        {
            long long tmp = 0;
            long long tmp1 = table[dep[u] - 1][k] - table[max(dep[lca] - 1, 0)][k];
            if (tmp1 < 0)
                tmp1 += mod;
            tmp1 %= mod;
            long long tmp2 = table[dep[v] - 1][k] - table[max(dep[lca] - 1, 0)][k];
            if (tmp2 < 0)
                tmp2 += mod;
            tmp2 %= mod;
            tmp = (tmp1 + tmp2 + (table[dep[lca] - 1][k] - table[max(dep[lca] - 2, 0)][k] + mod)) % mod;
            printf("%lld\n", tmp);
        }
    }
    return 0;
}