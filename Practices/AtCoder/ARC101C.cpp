// ARC101C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, head[MAX_N], current, g[MAX_N], dp[MAX_N][MAX_N], siz[MAX_N], tmp[MAX_N];

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
    siz[u] = 1, dp[u][1] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int j = 0; j <= siz[u]; j++)
                tmp[j] = dp[u][j], dp[u][j] = 0;
            for (int j = 0; j <= siz[u]; j++)
                for (int k = 0; k <= siz[edges[i].to]; k++)
                    dp[u][j + k] = (0LL + dp[u][j + k] + 1LL * tmp[j] * dp[edges[i].to][k] % mod) % mod;
            siz[u] += siz[edges[i].to];
        }
    for (int i = 0; i <= siz[u]; i++)
        dp[u][0] = (0LL + dp[u][0] + mod - 1LL * dp[u][i] * g[i] % mod) % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    g[0] = 1;
    for (int i = 2; i <= n; i += 2)
        g[i] = 1LL * g[i - 2] * (i - 1) % mod;
    dfs(1, 0), printf("%d\n", mod - dp[1][0]);
    return 0;
}