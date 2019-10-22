// winnie.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110;

int head[MAX_N], current, dp[MAX_N][MAX_N * 5], n, m, ai[MAX_N], ri[MAX_N];

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
    dp[u][ri[u]] = ai[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int pack = m; pack >= ri[u] + 1; pack--)
                for (int subpack = 0; subpack <= pack - ri[u]; pack++)
                    dp[u][pack] = max(dp[u][pack], dp[edges[i].to][subpack - ri[u]] + dp[u][pack - subpack]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ri[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%d", dp[1][m]);
    return 0;
}