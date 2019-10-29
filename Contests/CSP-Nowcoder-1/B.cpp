// B.cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)

using namespace std;

const int MAX_N = 1e5 + 200, MAX_K = 15, mod = 1e9 + 7;

int head[MAX_N], current, n, k, dp[MAX_N][MAX_K], prod[MAX_N][MAX_K];
int ans[MAX_N], ans2[MAX_N], org[MAX_N][MAX_K];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

namespace IO
{
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                                 \
    (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
         ? EOF                                                               \
         : *p1++)
inline int rd()
{
    int x = 0, f = 1;
    char c = gc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = gc();
    }
    while (isdigit(c))
        x = x * 10 + (c ^ 48), c = gc();
    return x * f;
}
} // namespace IO

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

void build_prod(int u, int fa)
{
    prod[u][0] = dp[u][0] % mod;
    for (int i = 1; i <= k; i++)
        prod[u][i] = (1LL * prod[u][i - 1] + 1LL * dp[u][i]) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            for (int j = 1; j <= k; j++)
                prod[u][j] = (1LL * prod[u][j] * prod[edges[i].to][j - 1] % mod);
}

void dfs(int u, int fa)
{
    dp[u][0] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs(edges[i].to, u);
            for (int j = 1; j <= k; j++)
                dp[u][j] += dp[edges[i].to][j - 1];
        }
    // get the prod;
    build_prod(u, fa);
}

void redfs(int u, int fa)
{
    // collecting data;
    for (int i = 0; i <= k; i++)
        ans[u] += dp[u][i];
    build_prod(u, 0);
    ans2[u] = prod[u][k];
    // to change the root;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            // make things ready for the subtree;
            for (int j = 1; j <= k; j++)
                dp[u][j] -= dp[edges[i].to][j - 1];
            for (int j = 1; j <= k; j++)
                dp[edges[i].to][j] += dp[u][j - 1];

            build_prod(u, edges[i].to);

            redfs(edges[i].to, u);

            for (int j = 1; j <= k; j++)
                dp[edges[i].to][j] -= dp[u][j - 1];
            for (int j = 1; j <= k; j++)
                dp[u][j] += dp[edges[i].to][j - 1];

            build_prod(edges[i].to, u);
            build_prod(u, 0);
            // rec on myself;
            for (int j = 1; j <= k; j++)
                prod[u][j] = 1LL * prod[u][j] * prod[edges[i].to][j - 1] % mod;
        }
}

int main()
{
    memset(head, -1, sizeof(head));
    n = IO::rd(), k = IO::rd();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = IO::rd(), v = IO::rd(), addpath(u, v), addpath(v, u);
    dfs(1, 0), redfs(1, 0);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    puts("");
    for (int i = 1; i <= n; i++)
        printf("%d ", ans2[i]);
    puts("");
    return 0;
}