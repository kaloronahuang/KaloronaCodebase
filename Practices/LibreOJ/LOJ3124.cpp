// LOJ3124.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3010, mod = 998244353;

int n, head[MAX_N], current, ai[MAX_N], bi[MAX_N], ci[MAX_N], dp[MAX_N][MAX_N], siz[MAX_N], inv[MAX_N], tmp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), memset(tmp, 0, sizeof(tmp));
            for (int j = 0; j <= (siz[u] * 3); j++)
                for (int k = 0; k <= (siz[edges[i].to] * 3); k++)
                    if (i & 1)
                    {
                        tmp[j + k] = (0LL + tmp[j + k] + mod - 1LL * dp[u][j] * dp[edges[i].to][k] % mod) % mod;
                        tmp[j] = (0LL + tmp[j] + 1LL * dp[u][j] * dp[edges[i].to][k] % mod) % mod;
                    }
                    else
                        tmp[j + k] = (0LL + tmp[j + k] + 1LL * dp[u][j] * dp[edges[i].to][k] % mod) % mod;
            memcpy(dp[u], tmp, sizeof(tmp));
            siz[u] += siz[edges[i].to];
        }
    for (int i = 0; i <= 3 * siz[u]; i++)
        dp[u][i] = 1LL * dp[u][i] * inv[i] % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &ai[i], &bi[i], &ci[i]);
        int sum_inv = fpow(ai[i] + bi[i] + ci[i], mod - 2);
        dp[i][1] = 1LL * ai[i] * sum_inv % mod;
        dp[i][2] = 2LL * bi[i] * sum_inv % mod;
        dp[i][3] = 3LL * ci[i] * sum_inv % mod;
    }
    inv[1] = inv[0] = 1;
    for (int i = 2; i <= (n * 3); i++)
        inv[i] = 1LL * inv[mod % i] * (mod - mod / i) % mod;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    int ans = 0;
    for (int i = 0; i <= (n * 3); i++)
        ans = (0LL + ans + dp[1][i]) % mod;
    printf("%d\n", ans);
    return 0;
}