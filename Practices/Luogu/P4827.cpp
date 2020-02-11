// P4827.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, MAX_K = 160, mod = 10007;

int n, limit, head[MAX_N], current, f[MAX_N][MAX_K], g[MAX_N][MAX_K], S[MAX_K][MAX_K], tmp[MAX_K];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void pre_dfs(int u, int fa)
{
    f[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            pre_dfs(edges[i].to, u), f[u][0] = (0LL + f[u][0] + f[edges[i].to][0]) % mod;
            for (int j = 1; j <= limit; j++)
                f[u][j] = (0LL + f[u][j] + f[edges[i].to][j - 1] + f[edges[i].to][j]) % mod;
        }
}

void dfs(int u, int fa)
{
    // make root;
    memcpy(g[u], f[u], sizeof(g[u]));
    if (fa != 0)
    {
        // transfer from father;
        memcpy(tmp, g[fa], sizeof(tmp));
        for (int j = 1; j <= limit; j++)
            tmp[j] = (0LL + tmp[j] + mod - f[u][j] + mod - f[u][j - 1]) % mod;
        tmp[0] = (0LL + tmp[0] + mod - f[u][0]) % mod;
        for (int j = 1; j <= limit; j++)
            g[u][j] = (0LL + g[u][j] + tmp[j] + tmp[j - 1]) % mod;
        g[u][0] = (0LL + g[u][0] + tmp[0]) % mod;
    }
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &limit);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    pre_dfs(1, 0), dfs(1, 0);
    S[0][0] = 1;
    for (int i = 1; i <= limit; i++)
        for (int j = 1; j <= limit; j++)
            S[i][j] = (0LL + S[i - 1][j - 1] + 1LL * j * S[i - 1][j] % mod) % mod;
    for (int i = 1; i <= n; i++)
    {
        int ans = 0;
        for (int j = 0, fac = 1; j <= limit; j++, fac = 1LL * fac * j % mod)
            ans = (0LL + ans + 1LL * S[limit][j] * g[i][j] % mod * fac % mod) % mod;
        printf("%d\n", ans);
    }
    return 0;
}