// CF1078C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int n, head[MAX_N], current, dp[MAX_N][3], tmp[3];

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
    dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            tmp[0] = 1LL * dp[u][0] * ((0LL + dp[edges[i].to][0] + dp[edges[i].to][2]) % mod) % mod;
            tmp[1] = (1LL * dp[u][0] * dp[edges[i].to][2] % mod + 1LL * dp[u][1] * ((dp[edges[i].to][0] + 2LL * dp[edges[i].to][2] % mod) % mod) % mod) % mod;
            tmp[2] = (1LL * dp[u][0] * (dp[edges[i].to][0] + dp[edges[i].to][1]) % mod + 1LL * dp[u][1] * (dp[edges[i].to][0] + dp[edges[i].to][1]) % mod + 1LL * dp[u][2] * ((dp[edges[i].to][0] + 2LL * dp[edges[i].to][2] % mod) % mod) % mod) % mod;
            swap(tmp, dp[u]);
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    printf("%d\n", (dp[1][0] + dp[1][2]) % mod);
    return 0;
}