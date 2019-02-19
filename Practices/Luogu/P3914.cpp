// P3914.cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 5050, MOD = 1e9 + 7;
int head[MAX_N], current, n, m, tmpx, tmpy, dp[MAX_N][MAX_N], tot[MAX_N];
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
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    for (int i = 1; i <= m; i++)
    {
        if (!dp[u][i])
            continue;
        for (int e = head[u]; e != -1; e = edges[e].nxt)
        {
            if (edges[e].to == fa)
                continue;
            dp[u][i] = (1LL * dp[u][i] * 1LL * (tot[edges[e].to] - dp[edges[e].to][i])) % MOD;
        }
        while (dp[u][i] < 0)
            dp[u][i] += MOD;
        tot[u] = (1LL * tot[u] + 1LL * dp[u][i]) % MOD;
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmpy);
        for (int j = 1; j <= tmpy; j++)
            scanf("%d", &tmpx), dp[i][tmpx] = 1;
    }
    for (int i = 1; i < n; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs(1, 0);
    printf("%d", tot[1] % MOD);
    return 0;
}