// P3703.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int head[MAX_N], current, n, m, dep[MAX_N], anti[MAX_N], lft[MAX_N], rig[MAX_N], upward[20][MAX_N];
int ptot;

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

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

struct node
{
    int tag, mx;
} nodes[MAX_N << 2];

void pushup(int p) { nodes[p].mx = max(nodes[lson].mx, nodes[rson].mx); }

void pushdown(int p)
{
    if (nodes[p].tag)
    {
        nodes[lson].tag += nodes[p].tag, nodes[lson].mx += nodes[p].tag;
        nodes[rson].tag += nodes[p].tag, nodes[rson].mx += nodes[p].tag;
        nodes[p].tag = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].mx = dep[anti[l]];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].mx += val, nodes[p].tag += val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].mx;
    pushdown(p);
    int ret = -0x3f3f3f3f;
    if (ql <= mid)
        ret = max(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = max(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

} // namespace SegmentTree

namespace LCT
{

#define lson ch[p][0]
#define rson ch[p][1]

int ch[MAX_N][2], fa[MAX_N], val[MAX_N];
bool tag[MAX_N];

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][ch[z][1] == y] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
}

void splay(int p)
{
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(fat) == check(p) ? fat : p);
}

int find(int p)
{
    while (lson)
        p = lson;
    return p;
}

void access(int p)
{
    int pt = 0;
    for (int pre = 0; p != 0; pre = p, p = fa[p])
    {
        splay(p);
        // rson stuff;
        if (rson)
            pt = find(rson), SegmentTree::update(lft[pt], rig[pt], 1, n, 1, 1);
        if (rson = pre)
            pt = find(pre), SegmentTree::update(lft[pt], rig[pt], 1, n, 1, -1);
        ch[p][1] = pre;
    }
}

} // namespace LCT

void dfs(int u, int fa)
{
    LCT::fa[u] = upward[0][u] = fa, lft[u] = ++ptot;
    anti[ptot] = u, dep[u] = dep[fa] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u);
    rig[u] = ptot;
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[upward[i][x]] >= dep[y])
            x = upward[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (upward[i][x] != upward[i][y])
            x = upward[i][x], y = upward[i][y];
    return upward[0][x];
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), LCT::fa[1] = 0, SegmentTree::build(1, n, 1);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            upward[i][j] = upward[i - 1][upward[i - 1][j]];
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            LCT::access(x);
        else if (opt == 2)
        {
            scanf("%d", &y);
            int lca = getLCA(x, y);
            int ans = SegmentTree::query(lft[x], lft[x], 1, n, 1) + SegmentTree::query(lft[y], lft[y], 1, n, 1) - (SegmentTree::query(lft[lca], lft[lca], 1, n, 1) * 2);
            printf("%d\n", ans + 1);
        }
        else
            printf("%d\n", SegmentTree::query(lft[x], rig[x], 1, n, 1));
    }
    return 0;
}