// P3242.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, INF = 0x3f3f3f3f;

int n, p, q, head[MAX_N], current, dfn[MAX_N], low[MAX_N], fa[20][MAX_N], dep[MAX_N];
int qcnt, ptot, ans[MAX_N], nodes[MAX_N], vec[MAX_N], vcnt;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

struct query
{
    int typ, x, lower, upper, k, val, id;
    bool operator<(const query &rhs) const { return x < rhs.x || (x == rhs.x && typ < rhs.typ); }
} queries[MAX_N], q1[MAX_N], q2[MAX_N];

inline char gc()
{
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}

int read()
{
    int x = 0, f = 1;
    char ch = gc();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch))
        x = (x << 3) + (x << 1) + (ch - '0'), ch = gc();
    return x * f;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fat)
{
    fa[0][u] = fat, dep[u] = dep[fat] + 1, dfn[u] = ++ptot;
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

int getSon(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[fa[i][x]] >= dep[y] + 1)
            x = fa[i][x];
    return x;
}

inline int lowbit(int x) { return x & (-x); }

inline void update(int qx, int d)
{
    for (; qx <= n; qx += lowbit(qx))
        nodes[qx] += d;
}

inline int querySum(int qx, int ret = 0)
{
    for (; qx != 0; qx -= lowbit(qx))
        ret += nodes[qx];
    return ret;
}

void solve(int l, int r, int ql, int qr)
{
    if (ql > qr)
        return;
    if (l == r)
    {
        for (int i = ql; i <= qr; i++)
            if (queries[i].typ == 1)
                ans[queries[i].id] = vec[l];
        return;
    }
    int mid = (l + r) >> 1, lcnt = 0, rcnt = 0;
    for (int i = ql; i <= qr; i++)
        if (queries[i].typ == 0)
            if (queries[i].k <= mid)
                update(queries[i].lower, queries[i].val), update(queries[i].upper + 1, -queries[i].val), q1[++lcnt] = queries[i];
            else
                q2[++rcnt] = queries[i];
        else
        {
            int ref_val = querySum(queries[i].lower);
            if (queries[i].k <= ref_val)
                q1[++lcnt] = queries[i];
            else
                q2[++rcnt] = queries[i], q2[rcnt].k -= ref_val;
        }
    for (int i = 1; i <= lcnt; i++)
        queries[ql + i - 1] = q1[i];
    for (int i = 1; i <= rcnt; i++)
        queries[ql + lcnt + i - 1] = q2[i];
    solve(l, mid, ql, ql + lcnt - 1), solve(mid + 1, r, ql + lcnt, qr);
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), p = read(), q = read();
    for (int i = 1, u, v; i <= n - 1; i++)
        u = read(), v = read(), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            fa[i][j] = fa[i - 1][fa[i - 1][j]];
    // to put rect above the axis;
    for (int id = 1; id <= p; id++)
    {
        int a = read(), b = read(), c = read();
        vec[++vcnt] = c;
        if (dfn[a] > dfn[b])
            swap(a, b);
        int lca = getLCA(a, b);
        if (lca == a)
        {
            int son = getSon(a, b);
            // the less at x-axis, bigger at y-axis;
            if (dfn[son] > 1)
            {
                queries[++qcnt] = query{0, 1, dfn[b], low[b], c, 1, 0};
                queries[++qcnt] = query{0, dfn[son], dfn[b], low[b], c, -1, 0};
            }
            if (low[son] < n)
            {
                queries[++qcnt] = query{0, dfn[b], low[son] + 1, n, c, 1, 0};
                queries[++qcnt] = query{0, low[b] + 1, low[son] + 1, n, c, -1, 0};
            }
        }
        else
        {
            queries[++qcnt] = query{0, dfn[a], dfn[b], low[b], c, 1, id};
            queries[++qcnt] = query{0, low[a] + 1, dfn[b], low[b], c, -1, id};
        }
    }
    sort(vec + 1, vec + vcnt + 1), vcnt = unique(vec + 1, vec + vcnt + 1) - (vec + 1);
    for (int i = 1; i <= qcnt; i++)
        queries[i].k = lower_bound(vec + 1, vec + 1 + vcnt, queries[i].k) - vec;
    for (int i = 1; i <= q; i++)
    {
        int x = read(), y = read(), k = read();
        if (dfn[x] > dfn[y])
            swap(x, y);
        queries[++qcnt] = query{1, dfn[x], dfn[y], 0, k, 0, i};
    }
    sort(queries + 1, queries + 1 + qcnt);
    solve(1, vcnt, 1, qcnt);
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    return 0;
}