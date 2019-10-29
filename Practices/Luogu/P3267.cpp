// P3267.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100;

int head[MAX_N], current, n, m, limit, cost[MAX_N];
int f[MAX_N][30], g[MAX_N][30];
bool tag[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    if (tag[u])
        f[u][0] = g[u][0] = cost[u];
    else
        f[u][0] = g[u][0] = 0;
    for (int i = 1; i <= limit; i++)
        f[u][i] = cost[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            for (int dep = limit; dep >= 0; dep--)
                f[u][dep] = min(f[u][dep] + g[edges[i].to][dep], min(g[u][dep + 1] + f[edges[i].to][dep + 1], f[u][dep] + f[edges[i].to][dep + 1]));
            for (int dep = limit; dep >= 0; dep--)
                f[u][dep] = min(f[u][dep + 1], f[u][dep]);
            g[u][0] = f[u][0];
            for (int dep = 1; dep <= limit + 1; dep++)
                g[u][dep] += g[edges[i].to][dep - 1];
            for (int dep = 1; dep <= limit + 1; dep++)
                g[u][dep] = min(g[u][dep], g[u][dep - 1]);
        }
    for (int dep = limit; dep >= 0; dep--)
        f[u][dep] = min(f[u][dep + 1], f[u][dep]);
    for (int dep = 1; dep <= limit + 1; dep++)
        g[u][dep] = min(g[u][dep], g[u][dep - 1]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cost[i]);
    scanf("%d", &m);
    for (int i = 1, tmp; i <= m; i++)
        scanf("%d", &tmp), tag[tmp] = true;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    memset(f, 0x3f, sizeof(f));
    int ans = 0x3f3f3f3f;
    dfs(1, 0);
    for (int i = 0; i <= limit; i++)
        ans = min(ans, f[1][i]);
    printf("%d", ans);
    return 0;
}