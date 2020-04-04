// T19706.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100;

int n, q, typ, lastans, col[MAX_N], roots[MAX_N], lft[MAX_N], rig[MAX_N], ptot, head[MAX_N], current;
int fa[20][MAX_N], dep[MAX_N], dtot, anti[MAX_N], pre[MAX_N];
set<int> cols[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct node
{
    int lson, rson, sum;
} nodes[MAX_N * 200];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum += val;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int mid = (l + r) >> 1, ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

inline int lowbit(int x) { return x & (-x); }

void update(int x, int y, int val)
{
    for (; x <= n; x += lowbit(x))
        roots[x] = update(y, 1, n, roots[x], val);
}

int query(int x, int y1, int y2)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += query(y1, y2, 1, n, roots[x]);
    return ret;
}

void dfs(int u)
{
    dep[u] = dep[fa[0][u]] + 1, lft[u] = ++dtot, anti[dtot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[0][u])
            fa[0][edges[i].to] = u, dfs(edges[i].to);
    rig[u] = dtot;
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

void update(int x, int d)
{
    set<int>::iterator it = cols[col[x]].find(lft[x]), bef, aft;
    aft = it, aft++, update(col[x], lft[x], d);
    if (aft != cols[col[x]].end())
        update(col[x], lft[getLCA(x, anti[*aft])], -d);
    if (it != cols[col[x]].begin())
    {
        bef = it, bef--, update(col[x], lft[getLCA(x, anti[*bef])], -d);
        if (aft != cols[col[x]].end())
            update(col[x], lft[getLCA(anti[*bef], anti[*aft])], d);
    }
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &q, &typ);
    for (int i = 1; i <= n; i++)
        scanf("%d", &col[i]);
    for (int i = 1, u, v; i < n; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    for (int i = 1; i <= n; i++)
    {
        int u = anti[i];
        update(col[u], i, 1), cols[col[u]].insert(i);
        if (pre[col[u]])
            update(col[u], lft[getLCA(u, pre[col[u]])], -1);
        pre[col[u]] = u;
    }
    while (q--)
    {
        int opt, x, l, r;
        scanf("%d%d%d", &opt, &x, &l), x ^= typ * lastans, l ^= typ * lastans;
        if (opt == 1)
            scanf("%d", &r), r ^= typ * lastans, printf("%d\n", lastans = query(r, lft[x], rig[x]) - query(l - 1, lft[x], rig[x]));
        else
            update(x, -1), cols[col[x]].erase(lft[x]), col[x] = l, cols[col[x]].insert(lft[x]), update(x, 1);
    }
    return 0;
}