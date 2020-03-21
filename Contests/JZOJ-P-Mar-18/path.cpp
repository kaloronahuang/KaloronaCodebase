// path.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, head[MAX_N], current, deg[MAX_N], fac[MAX_N], fac_inv[MAX_N], dep[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void fileIO()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
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

namespace chainSubtask
{

void subtaskHandler()
{
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1LL * fac[i - 1] * i % mod;
    fac_inv[n] = fpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
        fac_inv[i] = 1LL * fac_inv[i + 1] * (i + 1) % mod;
    printf("1 ");
    for (int i = 2; i <= n - 1; i++)
        printf("%lld ", 1LL * fac[n - 2] * fac_inv[i - 1] % mod * fac_inv[n - i - 1] % mod);
    puts("");
}

} // namespace chainSubtask

namespace backpackSubtask
{

int idx[MAX_N], ans[MAX_N], tag[MAX_N], fa[MAX_N];

void subtaskHandler()
{
    for (int rd = 1; rd <= n; rd++)
    {
        for (int i = 1; i <= rd; i++)
            idx[i] = i;
        do
        {
            for (int i = 1; i <= n; i++)
                tag[i] = 0;
            for (int i = 1; i <= rd; i++)
            {
                int x = i, y = idx[i];
                if (dep[x] > dep[y])
                    swap(x, y);
                while (dep[x] > dep[y])
                    tag[x]++, x = fa[x];
                while (x != y)
                    tag[x]++, tag[y]++, x = fa[x], y = fa[y];
            }
            int chk = 1;
            for (int i = 2; i <= n; i++)
                chk &= tag[i] == 1;
            ans[rd] += chk;
        } while (next_permutation(idx + 1, idx + 1 + n));
    }
}

} // namespace backpackSubtask

void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1, backpackSubtask::fa[u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), deg[u]++, deg[v]++;
    dfs(1, 0);
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        cnt += deg[i] == 2;
    if (cnt == n - 2)
        return chainSubtask::subtaskHandler(), 0;
    else
        return backpackSubtask::subtaskHandler(), 0;
    return 0;
}