// QOJ2030.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 3e5 + 200;

int n, q, seq[MAX_N], lft[MAX_N], rig[MAX_N], anti[MAX_N], root, fa[20][MAX_N], head[MAX_N], current;
int dep[MAX_N], ptot;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

namespace SegmentTree
{

ll nodes[MAX_N << 2], tag[MAX_N << 2];
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = seq[anti[l]]);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = nodes[lson] + nodes[rson];
}

void pushdown(int p, int l, int r)
{
    if (tag[p] != 0)
    {
        tag[lson] += tag[p], tag[rson] += tag[p];
        nodes[lson] += 1LL * tag[p] * (mid - l + 1), nodes[rson] += 1LL * tag[p] * (r - mid);
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] += 1LL * (r - l + 1) * val, tag[p] += val;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p] = nodes[lson] + nodes[rson];
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p, l, r);
    ll ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

#undef mid
#undef rson
#undef lson

} // namespace SegmentTree

void dfs_init(int u, int fat)
{
    dep[u] = dep[fat] + 1, fa[0][u] = fat, lft[u] = ++ptot, anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fat)
            dfs_init(edges[i].to, u);
    rig[u] = ptot;
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
    memset(head, -1, sizeof(head)), root = 1;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs_init(1, 0), root = 1, SegmentTree::build(1, n, 1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    while (q--)
    {
        int opt, x, y, z;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            root = x;
        else if (opt == 2)
        {
            scanf("%d%d", &y, &z);
            int lca = getLCA(x, y), lca1 = getLCA(root, x), lca2 = getLCA(root, y);
            int dlca = (dep[lca1] > dep[lca2] ? lca1 : lca2);
            if (dep[lca] > dep[dlca])
                dlca = lca;
            if (dlca == root)
                SegmentTree::update(1, n, 1, n, 1, z);
            else if (lft[dlca] <= lft[root] && rig[root] <= rig[dlca])
            {
                int u = root;
                for (int i = 19; i >= 0; i--)
                    if (dep[fa[i][u]] > dep[dlca])
                        u = fa[i][u];

                SegmentTree::update(1, n, 1, n, 1, z);
                SegmentTree::update(lft[u], rig[u], 1, n, 1, -z);
            }
            else
                SegmentTree::update(lft[lca], rig[lca], 1, n, 1, z);
        }
        else if (opt == 3)
        {
            // something different;
            // if there is an ancestor relationship;
            if (x == root)
                printf("%lld\n", SegmentTree::nodes[1]);
            else if (lft[x] <= lft[root] && lft[root] <= rig[x])
            {
                int u = root;
                for (int i = 19; i >= 0; i--)
                    if (dep[fa[i][u]] > dep[x])
                        u = fa[i][u];
                printf("%lld\n", SegmentTree::nodes[1] - SegmentTree::query(lft[u], rig[u], 1, n, 1));
            }
            else
                printf("%lld\n", SegmentTree::query(lft[x], rig[x], 1, n, 1));
        }
    }
    return 0;
}