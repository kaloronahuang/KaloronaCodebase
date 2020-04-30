// milkvisits1.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, dist[2][MAX_N], fa[20][MAX_N], head[MAX_N], current, dep[MAX_N];
char str[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat, dist[0][u] += dist[0][fat], dist[1][u] += dist[1][fat];
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
    // fileIO("milkvisits");
    memset(head, -1, sizeof(head));
    scanf("%d%d%s", &n, &q, str + 1);
    for (int i = 1; i <= n; i++)
        ((str[i] == 'H') ? dist[0][i] : dist[1][i])++;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int x, y;
        scanf("%d%d%s", &x, &y, str + 1);
        int *d = dist[str[1] != 'H'], lca = getLCA(x, y);
        printf("%c", '0' + (d[x] + d[y] - d[lca] - d[fa[0][lca]] > 0));
    }
    return 0;
}