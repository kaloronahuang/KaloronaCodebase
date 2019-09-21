// usmjeri.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 300100, mod = 1e9 + 7;

int head[MAX_N], current, dep[MAX_N], fa[20][MAX_N], n, m, val[MAX_N], mem[MAX_N << 1];
int queries[MAX_N][3];
bool side[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int find(int x)
{
    if (x == mem[x])
        return x;
    int pre = mem[x];
    mem[x] = find(mem[x]);
    side[x] ^= side[pre];
    return mem[x];
}

void unite(int x, int y)
{
    x = find(x);
    while (dep[x] - 2 >= dep[y])
    {
        int tmp = fa[0][x];
        tmp = find(tmp);
        mem[x] = tmp;
        x = find(x);
    }
}

int quick_pow(int bas, int tim)
{
    int ans = 1;
    for (; tim; tim >>= 1)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
    }
    return ans;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dep[u] = dep[fat] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 2 * n; i++)
        mem[i] = i;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int id = 1; id <= m; id++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        int lca = getLCA(x, y);
        queries[id][0] = x, queries[id][1] = y, queries[id][2] = lca;
        unite(x, lca), unite(y, lca);
    }
    for (int i = 1; i <= m; i++)
    {
        int x = queries[i][0], y = queries[i][1], lca = queries[i][2];
        if (x == lca || y == lca)
            continue;
        int fx = find(x), fy = find(y);
        if (fx == fy)
        {
            if ((side[x] ^ side[y]) != 1)
                puts("0"), exit(0);
            continue;
        }
        mem[fx] = fy;
        side[fx] = 1 ^ side[x] ^ side[y];
    }
    int ans = 1;
    for (int i = 2; i <= n; i++)
        if (find(i) == i)
            ans = 1LL * ans * 2 % mod;
    printf("%d", ans);
    return 0;
}