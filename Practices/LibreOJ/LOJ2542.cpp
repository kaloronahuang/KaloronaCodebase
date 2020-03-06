// LOJ2542.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20, mod = 998244353;

int n, q, start_pos, head[MAX_N], current, deg[MAX_N], degInv[MAX_N];
int cnt[1 << MAX_N], A[MAX_N], B[MAX_N], min_val[1 << MAX_N], ans[1 << MAX_N];

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

void dfs(int u, int fa, int S)
{
    if (S & (1 << (u - 1)))
        return (void)(A[u] = B[u] = 0);
    int tmpA = 0, tmpB = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u, S);
            tmpA = (0LL + tmpA + A[edges[i].to]) % mod, tmpB = (0LL + tmpB + B[edges[i].to]) % mod;
        }
    int coeff = fpow((0LL + mod - 1LL * tmpA * degInv[u] % mod + 1) % mod, mod - 2) % mod;
    A[u] = 1LL * degInv[u] * coeff % mod, B[u] = 1LL * (1 + 1LL * tmpB * degInv[u] % mod) % mod * coeff % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &q, &start_pos);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    for (int i = 1; i <= n; i++)
        degInv[i] = fpow(deg[i], mod - 2);
    for (int stat = 0; stat < (1 << n); stat++)
    {
        dfs(start_pos, 0, stat);
        min_val[stat] = B[start_pos], cnt[stat] = (cnt[stat >> 1] + (stat & 1));
        ans[stat] = (0LL + mod + ((cnt[stat] & 1) ? 1 : -1) * min_val[stat]) % mod;
    }
    for (int j = 0; j < n; j++)
        for (int stat = 0; stat < (1 << n); stat++)
            if (stat & (1 << j))
                ans[stat] = (0LL + ans[stat] + ans[stat ^ (1 << j)]) % mod;
    while (q--)
    {
        int k, stat = 0;
        scanf("%d", &k);
        for (int i = 1, val; i <= k; i++)
            scanf("%d", &val), stat ^= (1 << (val - 1));
        printf("%d\n", ans[stat]);
    }
    return 0;
}