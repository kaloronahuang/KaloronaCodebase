// CF-103389J.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_K = 220;

typedef long long ll;

int n, k, p, head[MAX_N], current, siz[MAX_N];
ll dp[MAX_N][MAX_K][2], tdp[MAX_K][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

void dfs(int u, int fa)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    siz[u] = 1;
    dp[u][0][1] = dp[u][1][0] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            int v = edges[i].to;
            memcpy(tdp, dp[u], sizeof(tdp));
            for (int sub1 = min(k << 1, siz[u]); sub1 >= 0; sub1--)
                for (int sub2 = min((k << 1) - sub1, siz[v]); sub2 >= 0; sub2--)
                {
                    tdp[sub1 + sub2][1] = max(tdp[sub1 + sub2][1], dp[u][sub1][1] + max(dp[v][sub2][0], dp[v][sub2][1]));
                    tdp[sub1 + sub2][0] = max(tdp[sub1 + sub2][0], max(dp[u][sub1][0] + max(dp[v][sub2][0], dp[v][sub2][1]), dp[u][sub1][1] + edges[i].weight + dp[v][sub2][1]));
                }
            memcpy(dp[u], tdp, sizeof(tdp)), siz[u] += siz[v];
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    ll *ptr = &dp[0][0][0];
    fill(ptr, ptr + MAX_N * MAX_K * 2, ll(-1e18));
    dfs(1, 0);
    ll ans = 0;
    for (int i = 0; i <= k; i++)
        ans = max(ans, 1LL * i * p + max(dp[1][i << 1][1], dp[1][i << 1][0]));
    printf("%lld\n", ans);
    return 0;
}