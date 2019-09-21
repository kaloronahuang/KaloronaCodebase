// dostavljac.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 550;

int head[MAX_N], current, n, m, ai[MAX_N];
ll dp[MAX_N][MAX_N][2];

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
    dp[u][1][0] = dp[u][1][1] = ai[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int k = m; k >= 0; k--)
            {
                for (int j = m - k; j >= 0; j--)
                {
                    if (j >= 1)
                        dp[u][j + k][0] = max(dp[u][j + k][0], dp[edges[i].to][j - 1][0] + dp[u][k][1]);
                    if (j >= 2)
                        dp[u][j + k][1] = max(dp[u][j + k][1], dp[edges[i].to][j - 2][1] + dp[u][k][1]);
                    if (j >= 2)
                        dp[u][j + k][0] = max(dp[u][j + k][0], dp[edges[i].to][j - 2][1] + dp[u][k][0]);
                }
            }
        }
}

int main()
{
    /*
    freopen("dostavljac.in", "r", stdin);
    freopen("dostavljac.out", "w", stdout);
    */
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    printf("%lld", max(dp[1][m][1], dp[1][m][0]));
    return 0;
}