// LOJ2032.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

const ll INF = 123456789123456789;

int n, q, head[MAX_N], current, siz[MAX_N], son[MAX_N], top[MAX_N], dep[MAX_N], up[MAX_N];
int lft[MAX_N], rig[MAX_N], anti[MAX_N], ptot;
ll dist[MAX_N];

struct edge
{
    int to, nxt, weight;
} edges[MAX_N << 1];

void addpath(int src, int dst, int weight)
{
    edges[current].to = dst, edges[current].weight = weight;
    edges[current].nxt = head[src], head[src] = current++;
}

namespace SegmentTree
{

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

struct node
{
    ll k, b, mn, mx, lx, rx;
} nodes[MAX_N << 2];

void build(int l, int r, int p)
{
    nodes[p].b = nodes[p].mn = INF, nodes[p].lx = dist[anti[l]], nodes[p].rx = dist[anti[r]];
    if (l == r)
        return;
    nodes[p].mx = dist[anti[mid]];
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p].mn = min(nodes[lson].mn, nodes[rson].mn);
}

void update(int ql, int qr, int l, int r, int p, ll k, ll b)
{
    if (ql <= l && r <= qr)
    {
        ll lx = nodes[p].lx, rx = nodes[p].rx, l0 = nodes[p].k * lx + nodes[p].b, r0 = nodes[p].k * rx + nodes[p].b;
        ll l1 = k * lx + b, r1 = k * rx + b;
        if (l0 <= l1 && r0 <= r1)
            return;
        if (l1 <= l0 && r1 <= r0)
        {
            nodes[p].k = k, nodes[p].b = b, nodes[p].mn = min(nodes[p].mn, min(l1, r1));
            return;
        }
        double mid_point = nodes[p].mx, mpt = double(nodes[p].b - b) / double(k - nodes[p].k);
        if (l0 < l1)
            if (mpt <= mid_point)
                update(ql, qr, l, mid, lson, nodes[p].k, nodes[p].b), nodes[p].k = k, nodes[p].b = b;
            else
                update(ql, qr, mid + 1, r, rson, k, b);
        else if (mpt <= mid_point)
            update(ql, qr, l, mid, lson, k, b);
        else
            update(ql, qr, mid + 1, r, rson, nodes[p].k, nodes[p].b), nodes[p].k = k, nodes[p].b = b;
        nodes[p].mn = min(nodes[p].mn, min(l1, r1)), nodes[p].mn = min(nodes[p].mn, min(nodes[lson].mn, nodes[rson].mn));
        return;
    }
    if (ql <= mid)
        update(ql, qr, l, mid, lson, k, b);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, k, b);
    nodes[p].mn = min(nodes[p].mn, min(nodes[lson].mn, nodes[rson].mn));
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].mn;
    ll ret = INF;
    if (nodes[p].b != INF)
        ret = min(nodes[p].k * dist[anti[max(ql, l)]], nodes[p].k * dist[anti[(min(qr, r))]]) + nodes[p].b;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

} // namespace SegmentTree

void dfs1(int u, int fa)
{
    siz[u] = 1, up[u] = fa, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dist[edges[i].to] = dist[u] + edges[i].weight;
            dfs1(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = siz[son[u]] < siz[edges[i].to] ? edges[i].to : son[u];
        }
}

void dfs2(int u, int org)
{
    lft[u] = ++ptot, top[u] = org, anti[ptot] = u;
    if (son[u])
        dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != up[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
    rig[u] = ptot;
}

int getLCA(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        x = up[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    return x;
}

void updateChain(int x, int y, ll k, ll b)
{
    while (top[x] != top[y])
        SegmentTree::update(lft[top[x]], lft[x], 1, n, 1, k, b), x = up[top[x]];
    SegmentTree::update(lft[y], lft[x], 1, n, 1, k, b);
}

ll query(int x, int y)
{
    ll ret = INF;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ret = min(ret, SegmentTree::query(lft[top[x]], lft[x], 1, n, 1));
        x = up[top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    ret = min(ret, SegmentTree::query(lft[x], lft[y], 1, n, 1));
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v, w; i <= n - 1; i++)
        scanf("%d%d%d", &u, &v, &w), addpath(u, v, w), addpath(v, u, w);
    dfs1(1, 0), dfs2(1, 1), SegmentTree::build(1, n, 1);
    while (q--)
    {
        int opt, s, t, a, b;
        scanf("%d%d%d", &opt, &s, &t);
        if (opt == 1)
        {
            int lca = getLCA(s, t);
            scanf("%d%d", &a, &b);
            updateChain(s, lca, -a, dist[s] * a + b), updateChain(t, lca, a, (dist[s] - (dist[lca] << 1)) * a + b);
        }
        else
            printf("%lld\n", query(s, t));
    }
    return 0;
}