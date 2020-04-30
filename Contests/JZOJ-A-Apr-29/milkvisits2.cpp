// milkvisits2.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, dist[2][MAX_N], fa[20][MAX_N], head[MAX_N], current, dep[MAX_N], roots[MAX_N], ptot, cols[MAX_N];
vector<int> mp;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 30];

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

int ripe(int x) { return lower_bound(mp.begin(), mp.end(), x) - mp.begin() + 1; }

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson);
    return p;
}

int query(int qx, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (l == r)
        return nodes[p].sum;
    if (qx <= mid)
        return query(qx, l, mid, nodes[p].lson);
    else
        return query(qx, mid + 1, r, nodes[p].rson);
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return x + y;
    nodes[x].sum += nodes[y].sum;
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
    return x;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    if (fat)
        roots[u] = merge(roots[u], roots[fat]);
    dep[u] = dep[fat] + 1, fa[0][u] = fat;
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

int main()
{
    // fileIO("milkvisits");
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &cols[i]), mp.push_back(cols[i]);
    sort(mp.begin(), mp.end()), mp.erase(unique(mp.begin(), mp.end()), mp.end());
    for (int i = 1; i <= n; i++)
        cols[i] = ripe(cols[i]), roots[i] = update(cols[i], 1, n, roots[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int x, y, typ;
        scanf("%d%d%d", &x, &y, &typ);
        if (mp[ripe(typ) - 1] != typ)
        {
            putchar('0');
            continue;
        }
        int lca = getLCA(x, y), ret = query(ripe(typ), 1, n, roots[x]) + query(ripe(typ), 1, n, roots[y]) - query(ripe(typ), 1, n, roots[lca]) - query(ripe(typ), 1, n, roots[fa[0][lca]]);
        putchar(ret > 0 ? '1' : '0');
    }
    return 0;
}