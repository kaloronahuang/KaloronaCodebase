// P4516.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, MAX_K = 110, mod = 1e9 + 7;

int n, k, dp[MAX_N][MAX_K][2][2], head[MAX_N], current, siz[MAX_N], tmp[MAX_K][2][2];

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
    dp[u][0][0][0] = dp[u][1][1][0] = 1, siz[u] = 1;
    for (int i = head[u], v; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(v = edges[i].to, u), memset(tmp, 0, sizeof(tmp));
            for (int sub1 = 0; sub1 <= k && sub1 <= siz[u]; sub1++)
                for (int sub2 = 0; sub1 + sub2 <= k && sub2 <= siz[v]; sub2++)
                {
                    if (dp[u][sub1][0][0])
                    {
                        tmp[sub1 + sub2][0][0] = (0LL + tmp[sub1 + sub2][0][0] + 1LL * dp[u][sub1][0][0] * dp[v][sub2][0][1] % mod) % mod;
                        tmp[sub1 + sub2][0][1] = (0LL + tmp[sub1 + sub2][0][1] + 1LL * dp[u][sub1][0][0] * dp[v][sub2][1][1] % mod) % mod;
                    }
                    if (dp[u][sub1][0][1])
                        tmp[sub1 + sub2][0][1] = (0LL + tmp[sub1 + sub2][0][1] + 1LL * dp[u][sub1][0][1] * ((0LL + dp[v][sub2][0][1] + dp[v][sub2][1][1]) % mod) % mod) % mod;
                    if (dp[u][sub1][1][0])
                    {
                        tmp[sub1 + sub2][1][0] = (0LL + tmp[sub1 + sub2][1][0] + 1LL * dp[u][sub1][1][0] * ((0LL + dp[v][sub2][0][1] + dp[v][sub2][0][0]) % mod) % mod) % mod;
                        tmp[sub1 + sub2][1][1] = (0LL + tmp[sub1 + sub2][1][1] + 1LL * dp[u][sub1][1][0] * ((0LL + dp[v][sub2][1][0] + dp[v][sub2][1][1]) % mod) % mod) % mod;
                    }
                    if (dp[u][sub1][1][1])
                    {
                        int sum = (0LL + dp[v][sub2][0][0] + dp[v][sub2][0][1] + dp[v][sub2][1][0] + dp[v][sub2][1][1]) % mod;
                        tmp[sub1 + sub2][1][1] = (0LL + tmp[sub1 + sub2][1][1] + 1LL * sum * dp[u][sub1][1][1] % mod) % mod;
                    }
                }
            siz[u] += siz[v], memcpy(dp[u], tmp, sizeof(tmp));
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &k);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), printf("%lld\n", (0LL + dp[1][k][0][1] + dp[1][k][1][1]) % mod);
    return 0;
}