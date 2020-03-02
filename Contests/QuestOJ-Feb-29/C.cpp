// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2020;

typedef long long ll;

int n, k, head[MAX_N], current, task, siz[MAX_N];
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
    memset(dp[u], 128, sizeof(dp[u]));
    dp[u][0] = dp[u][1] = 0, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
            for (int pack_siz = min(k, siz[u]); pack_siz >= 0; pack_siz--)
                for (int sub = 1; sub <= min(pack_siz, siz[edges[i].to]); sub++)
                    dp[u][pack_siz] = max(dp[u][pack_siz], dp[edges[i].to][sub] + dp[u][pack_siz - sub] + 2LL * edges[i].weight * min(sub, k - sub));
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &k, &task);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0), printf("%lld\n", dp[1][k]);
    return 0;
}