// P2542.cpp
#include <bits/stdc++.h>
#define pr pair<int, int>

using namespace std;

const int MAX_N = 101000;

int head[MAX_N], current, n, m, dep[MAX_N], q, ci[MAX_N], ai[MAX_N], bi[MAX_N], ans[MAX_N];
int ui[MAX_N], vi[MAX_N], siz[MAX_N], dfn[MAX_N], son[MAX_N], anti[MAX_N], top[MAX_N];
int nodes[MAX_N << 2], tag[MAX_N << 2], ptot, fa[MAX_N];
map<pr, int> mp;

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

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] = tag[rson] = 1;
        nodes[lson] = nodes[rson] = tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] = 0, tag[p] = 1;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    nodes[p] = nodes[lson] + nodes[rson];
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p);
    int ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

void update(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(dfn[top[x]], dfn[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    if (x != y)
        update(dfn[x] + 1, dfn[y], 1, n, 1);
}

int query(int x, int y)
{
    int ret = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret += query(dfn[top[x]], dfn[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    if (x != y)
        ret += query(dfn[x] + 1, dfn[y], 1, n, 1);
    return ret;
}

void dfs1(int u, int fat)
{
    siz[u] = 1, fa[u] = fat, dep[u] = dep[fat] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat && siz[edges[i].to] == 0)
        {
            dfs1(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = (siz[son[u]] < siz[edges[i].to] ? edges[i].to : son[u]);
        }
}

void dfs2(int u, int org)
{
    top[u] = org, dfn[u] = ++ptot, anti[ptot] = u;
    if (son[u] != 0)
        dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u] && fa[edges[i].to] == u)
            dfs2(edges[i].to, edges[i].to);
}

void dfs3(int u)
{
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (fa[edges[i].to] == u)
            dfs3(edges[i].to);
        else if (edges[i].to != fa[u] && dep[edges[i].to] < dep[u])
            update(u, edges[i].to);
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = 1);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = nodes[lson] + nodes[rson];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &ui[i], &vi[i]);
        if (ui[i] > vi[i])
            swap(ui[i], vi[i]);
    }
    while (++q && scanf("%d", &ci[q]) && ci[q] != -1 && scanf("%d%d", &ai[q], &bi[q]))
        ;
    q--, build(1, n, 1);
    for (int i = 1; i <= q; i++)
        if (ci[i] == 0)
            mp[make_pair(min(ai[i], bi[i]), max(ai[i], bi[i]))]++;
    for (int i = 1; i <= m; i++)
        if (mp.count(make_pair(ui[i], vi[i])) == 0)
            addpath(ui[i], vi[i]), addpath(vi[i], ui[i]);
    // needs to be reconstruct;
    dfs1(1, 0),
        dfs2(1, 1), dfs3(1);
    for (int i = q; i >= 1; i--)
        if (ci[i] == 0)
            update(ai[i], bi[i]);
        else
            ans[i] = query(ai[i], bi[i]);
    for (int i = 1; i <= q; i++)
        if (ci[i] == 1)
            printf("%d\n", ans[i]);
    return 0;
}