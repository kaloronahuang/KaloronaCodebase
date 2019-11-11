// P2014_N2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 330;

int head[MAX_N], current, n, m, val[MAX_N], dfn[MAX_N], nx[MAX_N], ptot, dp[MAX_N][MAX_N];
int anti[MAX_N];

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
    dfn[u] = ++ptot, anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    nx[dfn[u]] = ptot + 1;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m), n++, m++;
    for (int i = 2, fa; i <= n; i++)
        scanf("%d%d", &fa, &val[i]), addpath(++fa, i);
    dfs(1, 0);
    memset(dp, 128, sizeof(dp)), dp[1][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + val[anti[i]]);
            dp[nx[i]][j] = max(dp[nx[i]][j], dp[i][j]);
        }
    printf("%d", dp[n + 1][m]);
    return 0;
}