// P2416.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, m, dfn[MAX_N], low[MAX_N], stk[MAX_N], tail;
int ncnt, fa[20][MAX_N], dep[MAX_N], dist[MAX_N], ptot, aff[MAX_N], q, org[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];
vector<edge> G[MAX_N];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, stk[++tail] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
        else if (edges[i].to != fa)
            low[u] = min(low[u], dfn[edges[i].to]);
    if (dfn[u] == low[u] && (++ncnt))
        do
        {
            aff[stk[tail]] = ncnt;
        } while (stk[tail--] != u);
}

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    for (int i = 0, siz = G[u].size(); i < siz; i++)
        if (G[u][i].to != fat)
            dist[G[u][i].to] = org[G[u][i].to] + dist[u] + G[u][i].weight, dfs(G[u][i].to, u);
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
    for (int i = 1, u, v, w; i <= m; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    tarjan(1, 0);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[edges[i].to] == aff[u])
                org[aff[u]] += edges[i].weight;
            else
                G[aff[u]].push_back(edge{aff[edges[i].to], 0, edges[i].weight});
    dist[1] = org[1], dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    scanf("%d", &q);
    while (q--)
    {
        int u, v, lca;
        scanf("%d%d", &u, &v), lca = getLCA(aff[u], aff[v]);
        puts(dist[aff[u]] + dist[aff[v]] - (dist[lca] << 1) + org[lca] >= 1 ? "YES" : "NO");
    }
    return 0;
}
