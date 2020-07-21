// accompany.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0xcfcfcfcf;

int T, n, L, R, dp[2020][2020][2], head[MAX_N], current, siz[MAX_N], tmp[2020][2];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void fileIO(string str)
{
    freopen((str + ".in").c_str(), "r", stdin);
    freopen((str + ".out").c_str(), "w", stdout);
}

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1, dp[u][0][0] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), memset(tmp, 0xcf, sizeof(tmp));
            for (int j = 0; j < siz[edges[i].to]; j++)
                for (int k = 0; k < siz[u]; k++)
                {
                    if (max(dp[edges[i].to][j][0], dp[edges[i].to][j][1]) != INF && dp[u][k][0] != INF)
                        tmp[j + k][0] = max(tmp[j + k][0], max(dp[edges[i].to][j][0], dp[edges[i].to][j][1]) + dp[u][k][0]);
                    if (max(dp[edges[i].to][j][0], dp[edges[i].to][j][1]) != INF && dp[u][k][1] != INF)
                        tmp[j + k][1] = max(tmp[j + k][1], max(dp[edges[i].to][j][0], dp[edges[i].to][j][1]) + dp[u][k][1]);
                    if (dp[edges[i].to][j][0] != INF && dp[u][k][0] != INF)
                        tmp[j + k + 1][1] = max(tmp[j + k + 1][1], dp[edges[i].to][j][0] + dp[u][k][0] + edges[i].weight);
                }
            memcpy(dp[u], tmp, sizeof(dp[u])), siz[u] += siz[edges[i].to];
        }
}

int main()
{
    // fileIO("accompany");
    memset(head, -1, sizeof(head)), memset(dp, 0xcf, sizeof(dp));
    scanf("%d%d%d%d", &T, &n, &L, &R);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs(1, 0);
    for (int i = L; i <= R; i++)
        if (max(dp[1][i][0], dp[1][i][1]) == INF)
            printf("- ");
        else
            printf("%d ", max(dp[1][i][0], dp[1][i][1]));
    puts("");
    return 0;
}