// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, q, head[MAX_N], current, lft[MAX_N], rig[MAX_N], siz[MAX_N], son[MAX_N], anti[MAX_N];
int top[MAX_N], ptot, dep[MAX_N], fa[MAX_N];

namespace SegA
{

struct node
{
    int black_sum;
    bool rev_tag;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (nodes[p].rev_tag)
    {
        nodes[lson].black_sum = (mid - l + 1) - nodes[lson].black_sum;
        nodes[rson].black_sum = (r - mid) - nodes[rson].black_sum;
        nodes[lson].rev_tag ^= 1, nodes[rson].rev_tag ^= 1;
        nodes[p].rev_tag = 0;
    }
}

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].rev_tag ^= 1, nodes[p].black_sum = (r - l + 1) - nodes[p].black_sum;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    nodes[p].black_sum = nodes[lson].black_sum + nodes[rson].black_sum;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].black_sum;
    int ret = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

} // namespace SegA

namespace SegB
{

struct node
{
    int val;
    bool rev_tag;
} nodes[MAX_N << 2];

void pushdown(int p)
{
    if (nodes[p].rev_tag)
    {
        nodes[lson].val ^= 1, nodes[rson].val ^= 1;
        nodes[lson].rev_tag ^= 1, nodes[rson].rev_tag ^= 1;
        nodes[p].rev_tag = 0;
    }
}

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].rev_tag ^= 1, nodes[p].val ^= 1;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    nodes[p].val = nodes[lson].val ^ nodes[rson].val;
    return;
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p].val;
    pushdown(p);
    if (qx <= mid)
        return query(qx, l, mid, lson);
    else
        return query(qx, mid + 1, r, rson);
}

#undef mid
#undef rson
#undef lson

} // namespace SegB

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void pre_dfs(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, pre_dfs(edges[i].to), siz[u] += siz[edges[i].to];
            son[u] = siz[edges[i].to] > siz[son[u]] ? edges[i].to : son[u];
        }
}

void confirm(int u, int org)
{
    lft[u] = ++ptot, top[u] = org, dep[u] = dep[fa[u]] + 1;
    if (son[u] != 0)
        confirm(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            confirm(edges[i].to, edges[i].to);
    rig[u] = ptot;
}

void reversePath(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        SegA::update(lft[top[x]], lft[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    if (x != y)
        SegA::update(lft[x] + 1, lft[y], 1, n, 1);
}

void reverseBug(int x, int y)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        if (son[x])
            SegA::update(lft[son[x]], lft[son[x]], 1, n, 1);
        SegB::update(lft[top[x]], lft[x], 1, n, 1);
        x = fa[top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    if (son[y])
        SegA::update(lft[son[y]], lft[son[y]], 1, n, 1);
    if (son[fa[x]] == x)
        SegA::update(lft[x], lft[x], 1, n, 1);
    SegB::update(lft[x], lft[y], 1, n, 1);
}

int query(int x, int y)
{
    int ret = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        int cnt = SegA::query(lft[top[x]] + 1, lft[x], 1, n, 1);
        int top_up_weight = SegA::query(lft[top[x]], lft[top[x]], 1, n, 1);
        int top_color = SegB::query(lft[top[x]], 1, n, 1);
        int top_fa_color = SegB::query(lft[fa[top[x]]], 1, n, 1);
        int bouns = top_up_weight ^ top_color ^ top_fa_color;
        ret += cnt + bouns;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    if (x != y)
        ret += SegA::query(lft[x] + 1, lft[y], 1, n, 1);
    return ret;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    pre_dfs(1), confirm(1, 1), scanf("%d", &q);
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            reversePath(x, y);
        else if (opt == 2)
            reverseBug(x, y);
        else
            printf("%d\n", query(x, y));
    }
    return 0;
}