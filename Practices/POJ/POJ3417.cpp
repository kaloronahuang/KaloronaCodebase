// POJ3417.cpp
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 2e5 + 700;

int head[MAX_N], current, n, m, val[MAX_N], fa[20][MAX_N], dep[MAX_N];

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
            fa[0][edges[i].to] = u, dep[edges[i].to] = dep[u] + 1, dfs(edges[i].to, u);
}

void addup(int u, int fat)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            addup(edges[i].to, u), val[u] += val[edges[i].to];
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
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dep[1] = 1, dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        int lca = getLCA(u, v);
        val[u]++, val[v]++, val[lca] -= 2;
    }
    addup(1, 0);
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (val[i] == 0)
            ans += m;
        else if (val[i] == 1)
            ans++;
    printf("%lld", ans - m);
    return 0;
}