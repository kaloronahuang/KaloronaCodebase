// QOJ2033.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int head[MAX_N], current, n, q, f[MAX_N], g[MAX_N], deg[MAX_N], prefix_f[MAX_N], prefix_g[MAX_N];
int fat[20][MAX_N], dep[MAX_N], dist_f[MAX_N], dist_g[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs_f(int u, int fa)
{
    fat[0][u] = fa, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs_f(edges[i].to, u);
            f[u] = (0LL + f[edges[i].to] + f[u] + 1) % mod;
        }
    f[u] = (f[u] + 1) % mod;
}

void dfs_g(int u, int fa)
{
    int sum = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            sum = (0LL + sum + f[edges[i].to] + 1) % mod;
        else
            sum = (0LL + sum + g[u] + 1) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            g[edges[i].to] = (0LL + sum + mod - f[edges[i].to]) % mod, dfs_g(edges[i].to, u);
}

void dfs_collect(int u, int fa)
{
    prefix_f[u] = (0LL + prefix_f[fa] + f[u]) % mod, prefix_g[u] = (0LL + prefix_g[fa] + g[u]) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs_collect(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fat[i][x]] >= dep[y])
            x = fat[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fat[i][x] != fat[i][y])
            x = fat[i][x], y = fat[i][y];
    return fat[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs_f(1, 0), dfs_g(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fat[i][j] = fat[i - 1][fat[i - 1][j]];
    f[1] = g[1] = 0;
    dfs_collect(1, 0);
    while (q--)
    {
        int x, y, lca;
        scanf("%d%d", &x, &y), lca = getLCA(x, y);
        // x -> lca -> y;
        printf("%lld\n", ((0LL + prefix_f[x] + mod - prefix_f[lca]) % mod + (0LL + prefix_g[y] + mod - prefix_g[lca]) % mod) % mod);
    }
    return 0;
}