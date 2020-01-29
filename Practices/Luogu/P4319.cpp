// P4319.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 51000, MAX_E = 32766 * 3 + 200, MAX_TIME = 32766;

int n, m, e_tot, weights[MAX_N];

struct edge
{
    int src, dst, weight;
} edges[MAX_E];

namespace LCT
{

int ch[MAX_N][2], fa[MAX_N], val[MAX_N];
bool revTag[MAX_N];

#define lson (ch[p][0])
#define rson (ch[p][1])

// splay backend;

bool isRoot(int p) { return ch[fa[p]][0] != p && ch[fa[p]][1] != p; }

int check(int p) { return ch[fa[p]][1] == p; }

void pushup(int p)
{
    val[p] = p;
    if (lson && weights[val[lson]] > weights[val[p]])
        val[p] = val[lson];
    if (rson && weights[val[rson]] > weights[val[p]])
        val[p] = val[rson];
}

void pushdown(int p)
{
    if (revTag[p])
    {
        swap(lson, rson);
        revTag[lson] ^= 1, revTag[rson] ^= 1;
        revTag[p] = 0;
    }
}

void rotate(int x)
{
    int y = fa[x], z = fa[y], dir = check(x), w = ch[x][dir ^ 1];
    fa[x] = z;
    if (!isRoot(y))
        ch[z][check(y)] = x;
    fa[y] = x, ch[x][dir ^ 1] = y;
    fa[w] = y, ch[y][dir] = w;
    pushup(y), pushup(x);
}

void update(int p)
{
    if (!isRoot(p))
        update(fa[p]);
    pushdown(p);
}

void splay(int p)
{
    update(p);
    for (int fat = fa[p]; fat = fa[p], !isRoot(p); rotate(p))
        if (!isRoot(fat))
            rotate(check(p) == check(fat) ? fat : p);
}

// lct utilities;

void access(int p)
{
    for (int pre = 0; p; pre = p, p = fa[p])
        splay(p), rson = pre, pushup(p);
}

void makeRoot(int p) { access(p), splay(p), revTag[p] ^= 1, pushdown(p); }

int find(int p)
{
    access(p), splay(p), pushdown(p);
    while (lson)
        pushdown(p = lson);
    return p;
}

void split(int x, int y) { makeRoot(x), access(y), splay(y); }

void link(int x, int y) { makeRoot(x), fa[x] = y; }

void cut(int x, int y) { split(x, y), ch[y][0] = fa[x] = 0, pushup(y); }

int query(int x, int y)
{
    split(x, y);
    return val[y];
}

bool check(int x, int y)
{
    makeRoot(x);
    return find(y) == x;
}

#undef rson
#undef lson

} // namespace LCT

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

namespace SegmentTree
{

vector<int> sgt[(MAX_TIME << 2) + 200];

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(sgt[p].push_back(val));
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
}

} // namespace SegmentTree

pair<int, int> stk[MAX_N * 10];
int tail;
long long acc;

void solve(int l, int r, int p)
{
    using namespace SegmentTree;
    using namespace LCT;
    int cursor = tail;
    for (int idx = 0, siz = sgt[p].size(); idx < siz; idx++)
    {
        int eid = sgt[p][idx];
        if (check(edges[eid].src, edges[eid].dst))
        {
            int max_weight = query(edges[eid].src, edges[eid].dst) - n;
            if (edges[max_weight].weight <= edges[eid].weight)
                continue;
            acc -= edges[max_weight].weight;
            cut(edges[max_weight].src, max_weight + n), cut(max_weight + n, edges[max_weight].dst);
            stk[++tail] = make_pair(max_weight, -1);
        }
        acc += edges[eid].weight;
        link(edges[eid].src, eid + n), link(eid + n, edges[eid].dst);
        stk[++tail] = make_pair(eid, 1);
    }
    if (l == r)
        printf("%lld\n", acc + 1);
    else
        solve(l, mid, lson), solve(mid + 1, r, rson);
    while (tail > cursor)
    {
        pair<int, int> top = stk[tail--];
        if (top.second == 1)
            acc -= edges[top.first].weight, cut(edges[top.first].src, top.first + n), cut(top.first + n, edges[top.first].dst);
        else if (top.second == -1)
            acc += edges[top.first].weight, link(edges[top.first].src, top.first + n), link(top.first + n, edges[top.first].dst);
    }
}

int main()
{
    using namespace SegmentTree;

    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        e_tot++, scanf("%d%d%d", &edges[e_tot].src, &edges[e_tot].dst, &edges[e_tot].weight);
        update(1, MAX_TIME, 1, MAX_TIME, 1, e_tot), weights[n + e_tot] = edges[e_tot].weight;
    }
    scanf("%d", &m);
    for (int i = 1, l, r; i <= m; i++)
    {
        e_tot++, scanf("%d%d%d%d%d", &edges[e_tot].src, &edges[e_tot].dst, &edges[e_tot].weight, &l, &r);
        update(l, r, 1, MAX_TIME, 1, e_tot), weights[n + e_tot] = edges[e_tot].weight;
    }
    solve(1, MAX_TIME, 1);
    return 0;
}