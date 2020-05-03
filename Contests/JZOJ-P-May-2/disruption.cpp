// disruption.cpp
#include <bits/stdc++.h>

using namespace std;

void fileIO(string src)
{
    freopen((src + ".in").c_str(), "r", stdin);
    freopen((src + ".out").c_str(), "w", stdout);
}

const int MAX_N = 5e4 + 200, INF = 0x3f3f3f3f;

int n, m, head[MAX_N], current, lft[MAX_N], rig[MAX_N], anti[MAX_N], ui[MAX_N], vi[MAX_N], dep[MAX_N];
int son[MAX_N], siz[MAX_N], top[MAX_N], ptot, nodes[MAX_N << 2], tag[MAX_N << 2], ansBox[MAX_N], up[20][MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs1(int u, int fa)
{
    siz[u] = 1, dep[u] = dep[fa] + 1, up[0][u] = fa;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
        {
            dfs1(edges[i].to, u), siz[u] += siz[edges[i].to];
            son[u] = siz[son[u]] < siz[edges[i].to] ? edges[i].to : son[u];
        }
}

void dfs2(int u, int fa, int org)
{
    lft[u] = ++ptot, anti[lft[u]] = u, top[u] = org;
    if (son[u])
        dfs2(son[u], u, org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa && edges[i].to != son[u])
            dfs2(edges[i].to, u, edges[i].to);
    rig[u] = ptot;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// sgt;

void modify(int p, int val) { nodes[p] = min(nodes[p], val), tag[p] = min(tag[p], val); }

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void pushdown(int p)
{
    if (tag[p] != INF)
        modify(lson, tag[p]), modify(rson, tag[p]), tag[p] = INF;
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(modify(p, val));
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void build(int l, int r, int p)
{
    nodes[p] = tag[p] = INF;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

void output(int l, int r, int p)
{
    if (l == r)
        return (void)(ansBox[anti[l]] = nodes[p]);
    pushdown(p), output(l, mid, lson), output(mid + 1, r, rson);
}

void update(int x, int y, int val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(lft[top[x]], lft[x], 1, n, 1, val);
        x = up[0][top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    update(lft[x], lft[y], 1, n, 1, val);
}

int getLCA(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = 19; i >= 0; i--)
        if (dep[up[i][x]] >= dep[y])
            x = up[i][x];
    if (x == y)
        return x;
    for (int i = 19; i >= 0; i--)
        if (up[i][x] != up[i][y])
            x = up[i][x], y = up[i][y];
    return up[0][x];
}

int main()
{
    // fileIO("disruption");
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &ui[i], &vi[i]), addpath(ui[i], vi[i]), addpath(vi[i], ui[i]);
    dfs1(1, 0), dfs2(1, 0, 1), build(1, n, 1);
    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            up[i][j] = up[i - 1][up[i - 1][j]];
    while (m--)
    {
        int u, v, r, lca;
        scanf("%d%d%d", &u, &v, &r), lca = getLCA(u, v);
        if (dep[u] < dep[v])
            swap(u, v);
        int ud = u, vd = v;
        for (int i = 19; i >= 0; i--)
            if (dep[up[i][ud]] > dep[lca])
                ud = up[i][ud];
        if (lca == v)
            update(u, ud, r);
        else
        {
            for (int i = 19; i >= 0; i--)
                if (dep[up[i][vd]] > dep[lca])
                    vd = up[i][vd];
            update(u, ud, r), update(v, vd, r);
        }
    }
    output(1, n, 1);
    for (int i = 1; i <= n - 1; i++)
    {
        if (dep[ui[i]] > dep[vi[i]])
            swap(ui[i], vi[i]);
        if (ansBox[vi[i]] == INF)
            puts("-1");
        else
            printf("%d\n", ansBox[vi[i]]);
    }
    return 0;
}