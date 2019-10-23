// CF1249F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 220;

int n, k, ai[MAX_N], head[MAX_N], current, dp[MAX_N][MAX_N];

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
    dp[u][0] = ai[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    for (int dep = 0; dep < MAX_N; dep++)
        if (dep == 0)
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (edges[i].to != fa)
                    dp[u][dep] += dp[edges[i].to][max(k - dep - 1, 0)];
                else
                    continue;
        else
            for (int i = head[u]; i != -1; i = edges[i].nxt)
                if (edges[i].to != fa)
                {
                    int tmp = dp[edges[i].to][dep - 1];
                    for (int e = head[u]; e != -1; e = edges[e].nxt)
                        if (edges[e].to != fa && edges[e].to != edges[i].to)
                            tmp += dp[edges[e].to][max(dep - 1, k - dep - 1)];
                    dp[u][dep] = max(dp[u][dep], tmp);
                }
    for (int dep = MAX_N - 1; dep > 0; dep--)
        dp[u][dep - 1] = max(dp[u][dep - 1], dp[u][dep]);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k), k++;
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%d", dp[1][0]);
    return 0;
}