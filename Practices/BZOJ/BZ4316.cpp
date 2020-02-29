// BZ4316.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 51000, MAX_M = 61000;

int n, m, head[MAX_N], current, up[MAX_N], top[MAX_N], bottom[MAX_N], dep[MAX_N], f[MAX_N][2], g[MAX_N][2];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    dep[u] = dep[up[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == 0)
            up[edges[i].to] = u, dfs(edges[i].to);
}

void mark(int org, int bot)
{
    int p = bot;
    while (p != org)
        top[p] = org, bottom[p] = bot, p = up[p];
}

void collect(int u)
{
    f[u][1] = 1;
    if (u != bottom[u])
        g[u][1] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (dep[edges[i].to] == dep[u] + 1)
        {
            collect(edges[i].to);
            if (bottom[u] != bottom[edges[i].to])
                g[u][0] += f[edges[i].to][1], g[u][1] += g[edges[i].to][0];
            else
                g[u][0] += g[edges[i].to][1], g[u][1] += g[edges[i].to][0];
            if (top[edges[i].to] != u)
                f[u][0] += f[edges[i].to][1], f[u][1] += f[edges[i].to][0];
            else
                f[u][0] += f[edges[i].to][1], f[u][1] += g[edges[i].to][0];
        }
    f[u][1] = max(f[u][1], f[u][0]);
    g[u][1] = max(g[u][1], g[u][0]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1);
    for (int u = 1; u <= n; u++)
        for (int i = head[u]; i != -1; i = edges[i].nxt)
            if (dep[edges[i].to] > dep[u] && up[edges[i].to] != u)
                mark(u, edges[i].to);
    collect(1), printf("%d\n", f[1][1]);
    return 0;
}