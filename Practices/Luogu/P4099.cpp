// P4099.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1010, mod = 1e9 + 7;

int head[MAX_N], current, n, T, fac[MAX_N], fac_inv[MAX_N], f[MAX_N][MAX_N];
int siz[MAX_N], g[MAX_N];
char sign[20];

struct edge
{
    int to, nxt;
} edges[MAX_N];

vector<int> G[MAX_N];

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

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int C(int n_, int k_) { return 1LL * fac[n_] * fac_inv[k_] % mod * fac_inv[n_ - k_] % mod; }

void dfs(int u, int fa)
{
    memset(f[u], 0, sizeof(f[u])), siz[u] = 1, f[u][1] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            memcpy(g, f[u], sizeof(g)), memset(f[u], 0, sizeof(f[u]));
            // previous rank is j;
            for (int j = 1; j <= siz[u]; j++)
                // current rank is c, after merging;
                for (int c = j; c <= siz[edges[i].to] + j - 1; c++)
                {
                    int k_part = (0LL + f[edges[i].to][siz[edges[i].to]] + mod - f[edges[i].to][c - j]) % mod;
                    f[u][c] = (1LL * f[u][c] + 1LL * g[j] * C(c - 1, j - 1) % mod * C(siz[u] + siz[edges[i].to] - c, siz[u] - j) % mod * k_part % mod) % mod;
                }
            siz[u] += siz[edges[i].to];
        }
    for (int i = 0, siz_ = G[u].size(); i < siz_; i++)
        if (G[u][i] != fa)
        {
            dfs(G[u][i], u);
            memcpy(g, f[u], sizeof(g)), memset(f[u], 0, sizeof(f[u]));
            // previous rank is j;
            for (int j = 1; j <= siz[u]; j++)
                // current rank is c, after merging;
                for (int c = j + 1; c <= siz[G[u][i]] + j; c++)
                {
                    int k_part = f[G[u][i]][c - j] % mod;
                    f[u][c] = (1LL * f[u][c] + 1LL * g[j] * C(c - 1, j - 1) % mod * C(siz[u] + siz[G[u][i]] - c, siz[u] - j) % mod * k_part % mod) % mod;
                }
            siz[u] += siz[G[u][i]];
        }
    for (int i = 1; i <= siz[u]; i++)
        f[u][i] = (1LL * f[u][i] + f[u][i - 1]) % mod;
}

int main()
{
    scanf("%d", &T);
    for (int i = fac[0] = 1; i < MAX_N; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[MAX_N - 1] = quick_pow(fac[MAX_N - 1], mod - 2);
    for (int i = MAX_N - 2; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    while (T--)
    {
        memset(head, -1, sizeof(head)), current = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            G[i].clear();
        for (int i = 1, u, v; i <= n - 1; i++)
        {
            scanf("%d%s%d", &u, sign + 1, &v), u++, v++;
            if (sign[1] == '<')
                addpath(u, v), G[v].push_back(u);
            else
                addpath(v, u), G[u].push_back(v);
        }
        dfs(1, 0), printf("%d\n", f[1][n]);
    }
    return 0;
}