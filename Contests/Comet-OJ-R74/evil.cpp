// evil.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200, mod = 998244353;

int head[MAX_N], current, n, m, pow2[MAX_N], fa[25][MAX_N], mem[MAX_N];
int dist[MAX_N], dep[MAX_N], q;

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    edges[current].weight = weight, head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dist[edges[i].to] = (dist[u] + edges[i].weight) % mod, dfs(edges[i].to, u);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 24; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y])
            x = fa[i][x];
    if (x == y)
        return x;
    for (int i = 24; i >= 0; i--)
        if (fa[i][x] != fa[i][y])
            x = fa[i][x], y = fa[i][y];
    return fa[0][y];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = pow2[0] = 1; i <= m; i++)
        mem[i] = i, pow2[i] = 2LL * pow2[i - 1] % mod;
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        int fx = find(u), fy = find(v);
        if (fx != fy)
        {
            addpath(u, v, pow2[i]);
            addpath(v, u, pow2[i]);
            mem[fx] = fy;
        }
    }
    dfs(1, 0);
    for (int i = 1; i <= 24; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    scanf("%d", &q);
    while (q--)
    {
        int x, y, lca;
        scanf("%d%d", &x, &y), lca = getLCA(x, y);
        ll ans = dist[x] + dist[y] - (dist[lca] * 2LL);
        while (ans < 0)
            ans += mod;
        ans %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}