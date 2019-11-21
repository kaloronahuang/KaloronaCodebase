// P3177.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 2020;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int head[MAX_N], current, n, m, siz[MAX_N];
ll dp[MAX_N][MAX_N];

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
    siz[u] = 1, dp[u][0] = dp[u][1] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            for (int pack = min(siz[u], m); pack >= 0; pack--)
            {
                if (dp[u][pack] != -1)
                    dp[u][pack] += dp[edges[i].to][0] + 1LL * siz[edges[i].to] * (n - m - siz[edges[i].to]) * edges[i].weight;
                for (int subpack = min(pack, siz[edges[i].to]); subpack >= 1; subpack--)
                {
                    if (dp[u][pack - subpack] == -1)
                        continue;
                    ll val = (ll)(subpack * (m - subpack) + (siz[edges[i].to] - subpack) * (n - m - siz[edges[i].to] + subpack)) * edges[i].weight; //当前情况下连接子节点的边的贡献
                    dp[u][pack] = max(dp[u][pack], dp[u][pack - subpack] + dp[edges[i].to][subpack] + val);
                }
            }
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    memset(dp, -1, sizeof(dp)), dfs(1, -1);
    printf("%lld\n", dp[1][m]);
    return 0;
}