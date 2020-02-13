// class.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5500, mod = 1e9 + 7;

int n, m, head[MAX_N], current, fac[MAX_N], fac_inv[MAX_N], siz[MAX_N], gans, pow_table[MAX_N][MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("class.in", "r", stdin);
    freopen("class.out", "w", stdout);
}

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
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

int binomial(int n_, int k_) { return 1LL * fac[n_] * fac_inv[n_ - k_] % mod * fac_inv[k_] % mod; }

void dfs(int u, int fa)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
}

void calc(int u, int fa, int upweight)
{
    if (fa != 0)
        for (int xpy = 0; xpy <= (m << 1); xpy++)
            gans = (0LL + gans + 1LL * upweight * binomial(m << 1, xpy) % mod * min(xpy, (m << 1) - xpy) % mod * pow_table[siz[u]][xpy] % mod * pow_table[n - siz[u]][(m << 1) - xpy] % mod) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            calc(edges[i].to, u, edges[i].weight);
}

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    int max_level = (max(n, m) << 1);
    for (int i = fac[0] = 1; i <= max_level; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[max_level] = quick_pow(fac[max_level], mod - 2);
    for (int i = max_level - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    for (int i = 1; i < MAX_N; i++)
        for (int j = pow_table[i][0] = 1; j < MAX_N; j++)
            pow_table[i][j] = 1LL * pow_table[i][j - 1] * i % mod;
    dfs(1, 0), calc(1, 0, 0), printf("%d\n", gans);
    return 0;
}