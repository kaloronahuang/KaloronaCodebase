// connected.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 550, MAX_M = 40100, mod = 998244353, G = 3;

int n, m, head[MAX_N], current, ci[MAX_N], ans[MAX_M], siz[MAX_N];
int rev[MAX_M], poly_siz, poly_bit, dp[MAX_N][MAX_M];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

inline char nc()
{
    static char buf[1000000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char ch = nc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = nc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + ch - '0', ch = nc();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int fpow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * bas * ret % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

const int Gi = fpow(G, mod - 2);

void ntt_prep(int siz)
{
    poly_siz = 1, poly_bit = 0;
    while (poly_siz <= siz)
        poly_siz <<= 1, poly_bit++;
}

void ntt_initialize()
{
    for (int i = 0; i < poly_siz; i++)
        rev[i] = ((rev[i >> 1] >> 1) | ((i & 1) << (poly_bit - 1)));
}

void ntt(int *arr, int dft)
{
    for (int i = 0; i < poly_siz; i++)
        if (i < rev[i])
            swap(arr[i], arr[rev[i]]);
    for (int step = 1; step < poly_siz; step <<= 1)
    {
        int omega_n = fpow(dft == 1 ? G : Gi, (mod - 1) / (step << 1));
        for (int j = 0; j < poly_siz; j += (step << 1))
        {
            int omega_nk = 1;
            for (int k = j; k < j + step; k++, omega_nk = 1LL * omega_n * omega_nk % mod)
            {
                int t = 1LL * omega_nk * arr[k + step] % mod;
                arr[k + step] = (0LL + arr[k] + mod - t) % mod, arr[k] = (0LL + arr[k] + t) % mod;
            }
        }
    }
    if (dft == -1)
    {
        int inv = fpow(poly_siz, mod - 2);
        for (int i = 0; i < poly_siz; i++)
            arr[i] = 1LL * arr[i] * inv % mod;
    }
}

void dfs(int u, int fa)
{
    siz[u] = ci[u] % m, dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u), siz[u] = (0LL + siz[u] + siz[edges[i].to]) % m;
            // dp[u] * dp[edges[i].to], with modulo convolution;
            ntt(dp[u], 1), ntt(dp[edges[i].to], 1);
            for (int j = 0; j < poly_siz; j++)
                dp[u][j] = 1LL * dp[u][j] * dp[edges[i].to][j] % mod;
            ntt(dp[u], -1);
            for (int j = m; j < poly_siz; j++)
                dp[u][j % m] = (0LL + dp[u][j % m] + dp[u][j]) % mod, dp[u][j] = 0;
            continue;
        }
    for (int i = 0; i < m; i++)
        ans[i] = (0LL + ans[i] + dp[u][(siz[u] + m - i) % m]) % mod;
    dp[u][siz[u] % m] = (0LL + dp[u][siz[u] % m] + 1) % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read(), ntt_prep(m << 1), ntt_initialize();
    for (int i = 1; i <= n; i++)
        ci[i] = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 0; i < m; i++)
        printf("%d ", ans[i]);
    putchar('\n');
    return 0;
}