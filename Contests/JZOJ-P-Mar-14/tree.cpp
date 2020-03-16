// tree.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, K, mod, wi[MAX_N], head[MAX_N], current, fa[20][MAX_N], dep[MAX_N], pre[MAX_N], suf[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
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

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dep[u] = dep[fat] + 1;
    pre[u] = (1LL * pre[fat] * K % mod + wi[u]) % mod;
    suf[u] = (1LL * suf[fat] + 1LL * wi[u] * fpow(K, dep[u]) % mod) % mod;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][x];
}

int getDist(int x, int y)
{
    int lca = getLCA(x, y);
    int xchain = (0LL + pre[x] - 1LL * pre[fa[0][lca]] * fpow(K, dep[x] - dep[fa[0][lca]]) % mod) % mod;
    int ychain = 1LL * (0LL + suf[y] + mod - suf[lca]) % mod * fpow(fpow(K, mod - 2), dep[lca]) % mod * fpow(K, dep[x] - dep[lca] + 1) % mod;
    return (0LL + xchain + ychain) % mod;
}

namespace Subtask1
{

void subtaskHandler()
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
            {
                bool A = getDist(i, k) > 0, B = getDist(j, k) > 0, C = getDist(i, j) > 0;
                if (A == B && B == C)
                    ans++;
            }
    printf("%d\n", ans);
}

} // namespace Subtask1

namespace Subtask2
{

void subtaskHandler()
{
    long long ans = 0;
    int cnt[2] = {0, 0};
    for (int i = 1; i <= n; i++)
        cnt[pre[i]]++;
    ans = (1LL * cnt[0] * cnt[0] * cnt[0] + 1LL * cnt[1] * cnt[1] * cnt[1]);
    printf("%lld\n", ans);
}

} // namespace Subtask2

int main()
{
    // fileIO();
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &K, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%d", &wi[i]), wi[i] %= mod;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    if (n <= 50)
        Subtask1::subtaskHandler();
    else if (mod == 2 && K == 1)
        Subtask2::subtaskHandler();
    return 0;
}