// P3748.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int T, tx, n, p[2][2], head[MAX_N], current, deg[MAX_N], ans, dp[MAX_N][4];

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
    dp[u][0] = dp[u][2] = dp[u][3] = deg[u], dp[u][1] = 1;
    int acc = 0, rt = (fa == 0);
    for (int i = head[u], v; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(v = edges[i].to, u);
            ans = max({ans, dp[u][0] + dp[v][3] - rt, dp[u][3] + dp[v][0] - rt, dp[u][1] + dp[v][1] - 1, dp[u][1] + dp[v][2], dp[u][2] + dp[v][1] - rt, dp[u][2] + dp[v][2] - rt});
            dp[u][1] = max({dp[u][1], dp[v][1], dp[v][2] + 1});
            dp[u][3] = max({dp[u][3], dp[v][3] + deg[u] - 1, dp[v][0] + acc + deg[u] - 2, dp[u][0] + dp[v][1] - 1, dp[u][0] + dp[v][2] - 1, dp[u][2] + dp[v][0] - 1});
            dp[u][2] = max(dp[u][2], dp[u][0] + dp[v][0] - 1);
            dp[u][0] = max(dp[u][0], dp[v][0] + deg[u] - 1), dp[u][2] = max(dp[u][2], dp[u][0]), dp[u][3] = max(dp[u][3], dp[u][2]);
            acc = max(acc, dp[v][1]), acc = max(acc, dp[v][2]);
        }
}

int main()
{
    scanf("%d%d", &T, &tx);
    while (T--)
    {
        scanf("%d", &n);
        for (int i = 0; i < tx; i++)
            scanf("%d%d", &p[i][0], &p[i][1]);
        memset(head, -1, sizeof(int) * (n + 10));
        memset(deg, 0, sizeof(int) * (n + 10)), current = 0;
        for (int i = 1, u, v; i <= n - 1; i++)
            scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
        for (int i = 2; i <= n; i++)
            deg[i]--;
        dfs(1, ans = 0), printf("%d\n", ans);
    }
    return 0;
}