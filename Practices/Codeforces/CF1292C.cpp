// CF1292C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3030;

typedef long long ll;

int head[MAX_N], current, n, siz[MAX_N][MAX_N], fa[MAX_N][MAX_N];
ll f[MAX_N][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int org)
{
    siz[org][u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[org][u])
            fa[org][edges[i].to] = u, dfs(edges[i].to, org), siz[org][u] += siz[org][edges[i].to];
}

ll dp(int u, int v)
{
    if (u == v)
        return 0;
    if (f[u][v])
        return f[u][v];
    return (f[u][v] = max(dp(u, fa[u][v]), dp(v, fa[v][u])) + 1LL * siz[u][v] * siz[v][u]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    for (int i = 1; i <= n; i++)
        dfs(i, i);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            ans = max(ans, dp(i, j));
    printf("%lld\n", ans);
    return 0;
}