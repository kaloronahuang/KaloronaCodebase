// P2478.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, MAX_M = 2e6 + 200;

int n, m, head[MAX_N], current, dfn[MAX_N], low[MAX_N], dp[MAX_N][3], weights[MAX_N], ptot, up[MAX_N];
int ring[MAX_N], rlen, f[MAX_N][3];

struct edge
{
    int to, nxt;
} edges[MAX_M << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int calc(int beg, int fin)
{
    f[beg - 1][0] = 0, f[beg - 1][1] = dp[ring[beg - 1]][1], f[beg - 1][2] = dp[ring[beg - 1]][2];
    for (int i = beg; i <= fin + 1; i++)
    {
        f[i][0] = f[i - 1][2] + dp[ring[i]][0];
        f[i][2] = max(f[i - 1][2], f[i - 1][1]) + dp[ring[i]][2];
        f[i][1] = max(f[i - 1][0] + dp[ring[i]][2], max(f[i - 1][1], f[i - 1][2]) + dp[ring[i]][1]);
    }
    return max(f[fin + 1][1], f[fin + 1][2]);
}

void solve(int beg, int fin)
{
    rlen = 0, ring[++rlen] = beg;
    while (ring[rlen] != fin)
        ring[rlen + 1] = up[ring[rlen]], rlen++;
    dp[fin][1] = max(dp[fin][1] + calc(2, rlen - 2),
                     dp[fin][2] + max(dp[ring[1]][0] + dp[ring[2]][2] + calc(4, rlen - 2),
                                      calc(2, rlen - 4) + dp[ring[rlen - 2]][2] + dp[ring[rlen - 1]][0]));
    dp[fin][0] += calc(3, rlen - 3) + dp[ring[1]][2] + dp[ring[rlen - 1]][2];
    dp[fin][2] += calc(2, rlen - 2);
}

void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ptot, dp[u][0] = weights[u], up[u] = fa;
    int acc = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        if (dfn[edges[i].to] == 0)
            tarjan(edges[i].to, u), low[u] = min(low[u], low[edges[i].to]);
        else if (edges[i].to != fa)
            low[u] = min(low[u], dfn[edges[i].to]);
        if (low[edges[i].to] > dfn[u])
        {
            dp[u][0] += dp[edges[i].to][2], dp[u][2] += max(dp[edges[i].to][1], dp[edges[i].to][2]);
            acc = max(acc, dp[edges[i].to][0] - max(dp[edges[i].to][1], dp[edges[i].to][2]));
        }
    }
    dp[u][1] = dp[u][2] + acc;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (low[edges[i].to] == dfn[u] && up[edges[i].to] != u)
            solve(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &weights[i]);
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, 0), ans += max(dp[i][0], max(dp[i][1], dp[i][2]));
    printf("%d\n", ans);
    return 0;
}