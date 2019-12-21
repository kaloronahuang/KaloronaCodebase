// BZ3083.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 2e5 + 200;
const ll INF = 0x7fffffffffffffff;

int n, head[MAX_N], current;
int top[MAX_N], lft[MAX_N], rig[MAX_N], anti[MAX_N], dep[MAX_N];
int siz[MAX_N], son[MAX_N], ptot, fa[MAX_N], q, croot, upward[20][MAX_N];
ll wi[MAX_N], nodes[MAX_N << 2], tag_val[MAX_N << 2];
bool tag[MAX_N << 2];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1, upward[0][u] = fa[u];
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs(edges[i].to), siz[u] += siz[edges[i].to];
            if (siz[edges[i].to] > siz[son[u]])
                son[u] = edges[i].to;
        }
}

void dfs_confirm(int u, int org)
{
    lft[u] = ++ptot, anti[ptot] = u, top[u] = org;
    if (son[u] != 0)
        dfs_confirm(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u] && edges[i].to != fa[u])
            dfs_confirm(edges[i].to, edges[i].to);
    rig[u] = ptot;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p])
    {
        tag[lson] = tag[rson] = true;
        tag_val[lson] = tag_val[rson] = tag_val[p];
        nodes[lson] = nodes[rson] = tag_val[p];
        tag[p] = false, tag_val[p] = 0;
    }
}

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = wi[anti[l]]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] = val, tag[p] = true, tag_val[p] = val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p);
    ll ret = INF;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef rson
#undef lson

void update(int x, int y, ll val)
{
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(lft[top[x]], lft[x], 1, n, 1, val);
        x = fa[top[x]];
    }
    if (lft[x] > lft[y])
        swap(x, y);
    update(lft[x], lft[y], 1, n, 1, val);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1), dfs_confirm(1, 1), croot = 1;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &wi[i]);
    build(1, n, 1), scanf("%d", &croot);
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j <= n; j++)
            upward[i][j] = upward[i - 1][upward[i - 1][j]];
    while (q--)
    {
        int opt, x, y;
        ll z;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            croot = x;
        else if (opt == 2)
            scanf("%d%lld", &y, &z), update(x, y, z);
        else if (opt == 3)
        {
            // to have a discussion;
            if (croot == x)
                printf("%lld\n", nodes[1]);
            else if (lft[croot] <= lft[x] && lft[x] <= rig[croot])
                printf("%lld\n", query(lft[x], rig[x], 1, n, 1));
            else if (lft[x] <= lft[croot] && lft[croot] <= rig[x])
            {
                ll ret = INF;
                int u = croot;
                for (int i = 19; i >= 0; i--)
                    if (dep[upward[i][u]] > dep[x])
                        u = upward[i][u];
                if (lft[u] - 1 >= 1)
                    ret = min(ret, query(1, lft[u] - 1, 1, n, 1));
                if (rig[u] + 1 <= n)
                    ret = min(ret, query(rig[u] + 1, n, 1, n, 1));
                printf("%lld\n", ret);
            }
            else
                printf("%lld\n", query(lft[x], rig[x], 1, n, 1));
        }
    }
    return 0;
}