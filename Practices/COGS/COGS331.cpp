// COGS331.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int head[MAX_N], current, n, m, k, dp[MAX_N][MAX_N][2], tmp[MAX_N][2];
int siz[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1, dp[u][0][0] = dp[u][1][1] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            int apart = (m == 2) ? edges[i].weight : 0;
            memcpy(tmp, dp[u], sizeof(dp[u]));
            memset(dp[u], 0x3f, sizeof(dp[u]));
            for (int j = siz[u]; j >= 0; j--)
            {
                if (j > 0)
                    for (int k = j - 1; k >= 0; k--)
                        dp[u][j][1] = min(dp[u][j][1], min(dp[edges[i].to][k][0] + tmp[j - k][1], dp[edges[i].to][k][1] + tmp[j - k][1] + edges[i].weight));
                for (int k = j; k >= 0; k--)
                    dp[u][j][0] = min(dp[u][j][0], min(dp[edges[i].to][k][0] + tmp[j - k][0] + apart, dp[edges[i].to][k][1] + tmp[j - k][0]));
            }
        }
}

int main()
{
    freopen("dragon.in", "r", stdin);
    freopen("dragon.out", "w", stdout);
    memset(head, -1, sizeof(head)), memset(dp, 0x3f, sizeof(dp));
    scanf("%d%d%d", &n, &m, &k);
    // judge the NO SOLUTION PART;
    if (n - k < m - 1)
        printf("-1"), exit(0);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), printf("%d", dp[1][k][1]);
    return 0;
}