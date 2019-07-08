// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3005;

int n, limit, head[MAX_N], current, siz[MAX_N], dp[MAX_N][MAX_N], val[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa, int dep)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u, dep - 1), siz[u] += siz[edges[i].to];
    int bound = min(siz[u], dep);
    for (int i = 1; i <= bound; i++)
        dp[u][i] = val[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            for (int k = bound; k >= 1; k--)
                for (int a = 0; a + k <= bound; a++)
                    dp[u][a + k] = max(dp[u][a + k], dp[u][k] + dp[edges[i].to][a]);
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit);
    for (int i = 1; i <= n; i++)
        scanf("%d", &val[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0, limit);
    int ans = 0;
    for (int i = 1; i <= limit; i++)
        ans = max(ans, dp[1][i]);
    printf("%d", ans);
    return 0;
}