// B.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 1e9 + 7;

int n, head[MAX_N], current, fa[20][MAX_N], prefix[MAX_N], val[MAX_N], dep[MAX_N];
int mem[MAX_N], order[MAX_N], anses[MAX_N];
pair<int, int> diameters[MAX_N];

struct edge
{
    int from, to, nxt;
} edges[MAX_N << 1], org[MAX_N];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int find(int x) { return x == mem[x] ? x : mem[x] = find(mem[x]); }

void dfs(int u, int fat, int pre_val)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
    prefix[u] = val[u] + pre_val;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u, pre_val + val[u]);
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
    return prefix[x] + prefix[y] - prefix[lca] - prefix[fa[0][lca]];
}

int quick_pow(int bas, int tim)
{
    int ans = 1;
    while (tim)
    {
        if (tim & 1)
            ans = 1LL * ans * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    int ans = 1;
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), ans = 1LL * ans * tmp % mod, val[i] = tmp;
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u), org[i] = {u, v, 0};
    dfs(1, 0, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= n; i++)
        diameters[i] = make_pair(i, i), mem[i] = i;
    for (int i = 1; i <= n - 1; i++)
        scanf("%d", &order[i]);
    reverse(order + 1, order + n);
    anses[1] = ans;
    for (int idx = 2; idx <= n; idx++)
    {
        int id = order[idx - 1];
        int x = org[id].from, y = org[id].to;
        x = find(x), y = find(y);
        // merge these two;
        int u = diameters[x].first, v = diameters[x].second;
        int w = diameters[y].first, z = diameters[y].second;
        int w1 = getDist(u, v), w2 = getDist(w, z), tmp;
        int pans = -1, px, py;
        if ((tmp = getDist(u, v)) > pans)
            px = u, py = v, pans = tmp;
        if ((tmp = getDist(w, z)) > pans)
            px = w, py = z, pans = tmp;
        if ((tmp = getDist(u, w)) > pans)
            px = u, py = w, pans = tmp;
        if ((tmp = getDist(z, v)) > pans)
            px = z, py = v, pans = tmp;
        if ((tmp = getDist(u, z)) > pans)
            px = u, py = z, pans = tmp;
        if ((tmp = getDist(w, v)) > pans)
            px = w, py = v, pans = tmp;
        mem[y] = x, diameters[x] = make_pair(px, py);
        ans = 1LL * ans * quick_pow(1LL * w1 * w2 % mod, mod - 2) % mod * pans % mod;
        anses[idx] = ans;
    }
    reverse(anses + 1, anses + n + 1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", anses[i]);
    return 0;
}