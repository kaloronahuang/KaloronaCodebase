// jingdian.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int head[MAX_N], current, n, q, dp[MAX_N][MAX_N];

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
    dp[u][0] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int cap = 1; cap <= q; cap++)
                for (int j = 0; j <= cap - 1; j++)
                    dp[u][cap] = max(dp[u][cap], dp[u][cap - 1 - j] + dp[edges[i].to][j] + edges[i].weight);
        }
}

int main()
{
    freopen("jingdian.in", "r", stdin);
    freopen("jingdian.out", "w", stdout);
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0);
    printf("%d", dp[1][q]);
    return 0;
}