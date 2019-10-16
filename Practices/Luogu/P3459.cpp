// P3459.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int head[MAX_N], n, m, current, fa[20][MAX_N], dep[MAX_N], dfn[MAX_N], low[MAX_N], ptot;
int nodes[MAX_N << 2], tag[MAX_N << 2], mem[MAX_N], anti[MAX_N];
char opt[2];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p] * (mid - l + 1);
        nodes[rson] += tag[p] * (r - mid);
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = dep[anti[l]] - 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = nodes[lson] + nodes[rson];
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] += (r - l + 1) * val, tag[p] += val;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p] = nodes[lson] + nodes[rson];
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p];
    pushdown(p, l, r);
    if (qx <= mid)
        return query(qx, l, mid, lson);
    else
        return query(qx, mid + 1, r, rson);
}

#undef lson
#undef rson
#undef mid

inline int find(int x)
{
    return x == mem[x] ? x : mem[x] = find(mem[x]);
}

void unite(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    if (dep[fx] > dep[fy])
        swap(fx, fy);
    mem[fy] = fx;
}

void merge(int src, int dst)
{
    src = find(src), dst = find(dst);
    while (src != dst)
        unite(src, fa[0][src]), src = find(src);
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dfn[u] = ++ptot, anti[ptot] = u, dep[u] = dep[fat] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs(edges[i].to, u);
    low[u] = ptot;
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
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        mem[i] = i;
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    build(1, n, 1);
    scanf("%d", &m), m += n - 1;
    while (m--)
    {
        int a, b;
        scanf("%s%d", opt + 1, &a);
        if (opt[1] == 'A')
        {
            scanf("%d", &b);
            int lca = getLCA(a, b);
            if (dep[a] > dep[b])
                swap(a, b);
            if (a == b)
                continue;
            if (lca == a)
            {
                int val = -(query(dfn[find(b)], 1, n, 1) - query(dfn[find(lca)], 1, n, 1));
                update(dfn[b], low[b], 1, n, 1, val);
            }
            else
            {
                int val1 = -(query(dfn[find(a)], 1, n, 1) - query(dfn[find(lca)], 1, n, 1));
                int val2 = -(query(dfn[find(b)], 1, n, 1) - query(dfn[find(lca)], 1, n, 1));
                update(dfn[a], low[a], 1, n, 1, val1);
                update(dfn[b], low[b], 1, n, 1, val2);
            }
            merge(a, lca), merge(b, lca);
        }
        else
            printf("%d\n", query(dfn[find(a)], 1, n, 1));
    }
    return 0;
}