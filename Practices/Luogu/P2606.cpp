// P2606.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

int head[MAX_N], current, n, mod, siz[MAX_N], fac[MAX_N], fac_inv[MAX_N];
int dp[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int quick_pow(int bas, int tim)
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

void dfs(int u)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dfs(edges[i].to), siz[u] += siz[edges[i].to];
    dp[u] = fac[siz[u] - 1];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        dp[u] = 1LL * dp[u] * fac_inv[siz[edges[i].to]] % mod * dp[edges[i].to] % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &mod);
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = quick_pow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;

    for (int i = 1; i <= n; i++)
    {
        if ((i << 1) <= n)
            addpath(i, i << 1);
        if (((i << 1) | 1) <= n)
            addpath(i, (i << 1) | 1);
    }

    dfs(1), printf("%d\n", dp[1]);
    return 0;
}