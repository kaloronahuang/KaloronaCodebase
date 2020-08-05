// ARC087F.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5050, mod = 1e9 + 7;

int n, head[MAX_N], current, siz[MAX_N], gcnt, fac[MAX_N], fac_inv[MAX_N], gpt, dp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void getSiz(int u, int fa)
{
    int max_part = 0;
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            getSiz(edges[i].to, u), max_part = max(max_part, siz[edges[i].to]);
            siz[u] += siz[edges[i].to];
        }
    max_part = max(max_part, n - siz[u]);
    if (max_part <= (n >> 1))
        gcnt++, gpt = u;
}

void dfs(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
}

int binomial(int n_, int k_) { return (n_ < k_) ? 0 : 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

int permutation(int n_, int k_) { return (n_ < k_) ? 0 : 1LL * fac[n_] * fac_inv[n_ - k_] % mod; }

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    getSiz(1, 0);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[0] = fac_inv[1] = 1;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * (mod - mod / i) * fac_inv[mod % i] % mod;
    for (int i = 2; i < MAX_N; i++)
        fac_inv[i] = 1LL * fac_inv[i - 1] * fac_inv[i] % mod;
    if (gcnt == 2)
    {
        printf("%lld\n", 1LL * fac[n >> 1] * fac[n >> 1] % mod);
        return 0;
    }
    dfs(gpt, 0), dp[0] = 1;
    int tot_siz = 0;
    for (int i = head[gpt]; i != -1; i = edges[i].nxt)
    {
        tot_siz += siz[edges[i].to];
        for (int j = tot_siz; j >= 0; j--)
            for (int k = 1; k <= min(siz[edges[i].to], j); k++)
            {
                int tmp = 1LL * dp[j - k] * binomial(siz[edges[i].to], k) % mod * permutation(siz[edges[i].to], k) % mod;
                dp[j] = (0LL + dp[j] + tmp) % mod;
            }
    }
    int ans = 0;
    for (int i = 0, opt = 1; i <= n; i++, opt = mod - opt)
        ans = (0LL + ans + 1LL * opt * dp[i] % mod * fac[n - i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}