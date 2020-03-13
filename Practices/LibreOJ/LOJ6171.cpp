// LOJ6171.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;
const double INF = 1e99;

int T, n, m, p, head[MAX_N], current, deg[MAX_N];
double dist[MAX_N], dp[MAX_N][MAX_N], cost[MAX_N][MAX_N];

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
    if (deg[u] == 1)
        return (void)(dist[u] = 1);
    dist[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), dist[u] += dist[edges[i].to] + 1;
    dist[u] /= 1.0 * (deg[u] - 1);
}

void solve(int dep, int l, int r, int LB, int RB)
{
    if (LB > RB)
        return;
    int mid = (LB + RB) >> 1, gpt = l, upper = min(r, mid - 1);
    dp[dep][mid] = INF;
    for (int i = l; i <= upper; i++)
        if (dp[dep - 1][i] + cost[i][mid] < dp[dep][mid])
            dp[dep][mid] = dp[dep - 1][i] + cost[i][mid], gpt = i;
    solve(dep, l, gpt, LB, mid - 1), solve(dep, gpt, r, mid + 1, RB);
}

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(dp, 0, sizeof(dp)), memset(cost, 0, sizeof(cost)), memset(deg, 0, sizeof(deg));
        memset(dist, 0, sizeof(dist)), memset(head, -1, sizeof(head));
        current = 0;
        scanf("%d%d%d", &n, &m, &p);
        for (int i = 1, a, b; i <= m - n; i++)
            scanf("%d%d", &a, &b), addpath(a, b), addpath(b, a), deg[a]++, deg[b]++;
        for (int u = 1; u <= n; u++)
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                dfs(edges[i].to, u);
        for (int u = 1; u <= n; u++)
        {
            cost[u][u] = 0;
            for (int v = u + 1; v <= n; v++)
            {
                cost[u][v] = cost[u][v - 1] + 1;
                for (int i = head[v - 1]; i != -1; i = edges[i].nxt)
                    cost[u][v] += cost[u][v - 1] + 1 + dist[edges[i].to];
            }
        }
        dp[1][1] = 0;
        for (int i = 2; i <= n; i++)
            dp[1][i] = INF;
        for (int i = 2; i <= p; i++)
            solve(i, 1, n, 1, n);
        printf("%.4lf\n", dp[p][n]);
    }
    return 0;
}