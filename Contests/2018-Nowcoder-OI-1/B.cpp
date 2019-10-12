// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, dep[MAX_N], fa[20][MAX_N], current, head[MAX_N], lft, rig;
int siz[MAX_N], cnt[MAX_N], outcnt[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            fa[0][edges[i].to] = u, dep[edges[i].to] = dep[u] + 1;
            dfs(edges[i].to);
            siz[u] += siz[edges[i].to];
            cnt[u] = (1LL * cnt[u] + 1LL * siz[edges[i].to] * (siz[edges[i].to] - 1) / 2) % mod;
        }
    cnt[u] = (1LL * siz[u] * (siz[u] - 1) / 2 - 1LL * cnt[u] + mod) % mod;
}

void dfs2(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
        {
            outcnt[edges[i].to] = ((1LL * outcnt[u] + 1LL * cnt[u] - 1LL * siz[u] * (siz[u] - 1) / 2 - 1LL * (n - siz[u]) * (n - siz[u] - 1) / 2 +
                                    1LL * siz[edges[i].to] * (siz[edges[i].to] - 1) / 2 + 1LL * (n - siz[edges[i].to]) * (n - siz[edges[i].to] - 1) / 2)) %
                                  mod;
            while (outcnt[edges[i].to] < 0)
                outcnt[edges[i].to] += mod;
            dfs2(edges[i].to);
        }
}

int get(int x, int y)
{
    for (int i = 19; i >= 0; i--)
        if (y & (1 << i))
            x = fa[i][x];
    return x;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &lft, &rig);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    dfs2(1);
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int up = get(i, lft - 1), lower = get(i, rig);
        ans = (ans + (2LL * cnt[i] + 1) * (outcnt[up] - outcnt[lower] + mod) + 1LL * cnt[i] * (dep[up] - dep[lower]) % mod) % mod;
    }
    printf("%lld", ans);
    return 0;
}