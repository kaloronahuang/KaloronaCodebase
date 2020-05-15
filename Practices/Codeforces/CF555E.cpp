// CF555E.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

int n, m, q, head[MAX_N], current, dfn[MAX_N], low[MAX_N], ptot, tag[2][MAX_N];
int aff[MAX_N], ncnt, block[MAX_N], up[20][MAX_N], dep[MAX_N];
vector<int> G[MAX_N];
bool vis[MAX_N];

struct edge
{
    int to, nxt;
    bool tag;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dfn[edges[i].to] == 0)
        {
            tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
            if (low[edges[i].to] > dfn[u])
                edges[i].tag = edges[i ^ 1].tag = true;
        }
        else if (edges[i].to != fa)
            low[u] = min(dfn[edges[i].to], low[u]);
}

void mark(int u, int fa, int col)
{
    aff[u] = col;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && !edges[i].tag && aff[edges[i].to] == 0)
            mark(edges[i].to, u, col);
}

void dfs(int u, int fa, int org)
{
    dep[u] = dep[fa] + 1, up[0][u] = fa, block[u] = org;
    for (int v : G[u])
        if (v != fa)
            dfs(v, u, org);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

void collect(int u, int fa)
{
    vis[u] = true;
    for (int v : G[u])
        if (v != fa)
            collect(v, u), tag[0][u] += tag[0][v], tag[1][u] += tag[1][v];
}

int main()
{
    memset(head, -1, sizeof(head)), scanf("%d%d%d", &n, &m, &q);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0);
    for (int i = 1; i <= n; i++)
        if (aff[i] == 0)
            mark(i, 0, ++ncnt);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (aff[u] != aff[edges[i].to])
                G[aff[u]].push_back(aff[edges[i].to]);
    int bcnt = 0;
    for (int i = 1; i <= ncnt; i++)
        if (block[i] == 0)
            dfs(i, 0, ++bcnt);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= ncnt; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    while (q--)
    {
        int x, y, lca;
        scanf("%d%d", &x, &y), x = aff[x], y = aff[y];
        if (block[x] != block[y])
            puts("No"), exit(0);
        lca = getLCA(x, y);
        tag[0][x]++, tag[0][lca]--, tag[1][lca]--, tag[1][y]++;
    }
    for (int i = 1; i <= ncnt; i++)
        if (!vis[i])
            collect(i, 0);
    bool flag = true;
    for (int i = 1; i <= ncnt; i++)
        flag &= (tag[1][i] == 0 || tag[0][i] == 0);
    puts(flag ? "Yes" : "No");
    return 0;
}