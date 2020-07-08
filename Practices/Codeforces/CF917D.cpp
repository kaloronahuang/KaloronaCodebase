// CF917D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 110, mod = 1e9 + 7;

int n, head[MAX_N], current, binomial[MAX_N][MAX_N], siz[MAX_N];
int f[MAX_N][MAX_N][MAX_N], tmp[MAX_N][MAX_N], prod[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

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
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

void dfs(int u, int fa)
{
    siz[u] = 1, f[u][1][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            memset(tmp, 0, sizeof(tmp));
            for (int j = 1; j <= siz[u]; j++)
                for (int k = 1; k <= siz[edges[i].to]; k++)
                    for (int a = 0; a < siz[u]; a++)
                        for (int b = 0; b < siz[edges[i].to]; b++)
                        {
                            tmp[j + k][a + b + 1] = (0LL + tmp[j + k][a + b + 1] + 1LL * f[u][j][a] * f[edges[i].to][k][b] % mod) % mod;
                            tmp[j][a + b] = (0LL + tmp[j][a + b] + 1LL * f[u][j][a] * f[edges[i].to][k][b] % mod * k % mod) % mod;
                        }
            memcpy(f[u], tmp, sizeof(tmp));
            siz[u] += siz[edges[i].to];
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    binomial[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        binomial[i][0] = 1;
        for (int j = 1; j <= i; j++)
            binomial[i][j] = (0LL + binomial[i - 1][j - 1] + binomial[i - 1][j]) % mod;
    }
    dfs(1, 0);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < n; j++)
            prod[j] = (0LL + prod[j] + 1LL * f[1][i][j] * i % mod) % mod;
    prod[n - 1] = 1;
    for (int i = 0; i < n - 1; i++)
        prod[i] = 1LL * prod[i] * fpow(n, n - i - 2) % mod;
    for (int i = n - 1; i >= 0; i--)
        for (int j = i + 1; j < n; j++)
            prod[i] = (0LL + prod[i] + mod - 1LL * binomial[j][i] * prod[j] % mod) % mod;
    for (int i = 0; i < n; i++)
        printf("%d ", prod[i]);
    puts("");
    return 0;
}