// P3384.cpp
#include <bits/stdc++.h>
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;
const int MAX_N = 1e5 + 100;
int head[MAX_N], current, tmpx, tmpy, tot, dfn[MAX_N], antidfn[MAX_N], lazy[MAX_N << 2], n, m, root, opt;
int son[MAX_N], top[MAX_N], dep[MAX_N], fa[MAX_N], siz[MAX_N], tree[MAX_N << 2], pmod, low[MAX_N];
int src[MAX_N];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
// tree stuff.
void addpath(int src, int dst)
{
    edges[current].to = dst;
    edges[current].nxt = head[src], head[src] = current++;
}
// segment tree;
void build(int l, int r, int p)
{
    if (l == r)
    {
        tree[p] = src[antidfn[l]] % pmod;
        return;
    }
    build(l, mid, ls), build(mid + 1, r, rs);
    tree[p] = (tree[ls] + tree[rs]) % pmod;
}
void update(int ql, int qr, int l, int r, int p, int c)
{
    if (ql <= l && r <= qr)
    {
        tree[p] += (r - l + 1) * c % pmod, lazy[p] += c;
        return;
    }
    if (lazy[p] && l != r)
    {
        tree[ls] = (tree[ls] + lazy[p] * (mid - l + 1)) % pmod;
        tree[rs] = (tree[rs] + lazy[p] * (r - mid)) % pmod;
        lazy[ls] += lazy[p], lazy[rs] += lazy[p];
    }
    lazy[p] = 0;
    if (ql <= mid)
        update(ql, qr, l, mid, ls, c);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rs, c);
    tree[p] = (tree[ls] + tree[rs]) % pmod;
}
int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p] % pmod;
    int ans = 0;
    if (lazy[p] && l != r)
    {
        tree[ls] = (tree[ls] + lazy[p] * (mid - l + 1)) % pmod;
        tree[rs] = (tree[rs] + lazy[p] * (r - mid)) % pmod;
        lazy[ls] += lazy[p], lazy[rs] += lazy[p];
    }
    lazy[p] = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, ls), ans %= pmod;
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rs), ans %= pmod;
    return ans % pmod;
}
// tree operations;
void dfs1(int u)
{
    siz[u] = 1;
    int key = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        int to = edges[i].to;
        if (to == fa[u])
            continue;
        fa[to] = u, dep[to] = dep[u] + 1;
        dfs1(to);
        siz[u] += siz[to];
        if (siz[to] > key)
            son[u] = to, key = siz[to];
    }
}
void dfs2(int u, int t)
{
    dfn[u] = ++tot, antidfn[tot] = u, top[u] = t, low[u] = tot;
    if (son[u] == 0)
        return;
    dfs2(son[u], t);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
    low[u] = tot;
}
void updateRange(int x, int y, int c)
{
    c %= pmod;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(dfn[top[x]], dfn[x], 1, n, 1, c);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(dfn[x], dfn[y], 1, n, 1, c);
}
int queryRange(int x, int y)
{
    int ans = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = (ans + query(dfn[top[x]], dfn[x], 1, n, 1)) % pmod;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans = (ans + query(dfn[x], dfn[y], 1, n, 1)) % pmod;
    return ans;
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d%d", &n, &m, &root, &pmod);
    for (int i = 1; i <= n; i++)
        scanf("%d", &src[i]);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs1(root), dfs2(root, root);
    build(1, n, 1);
    int x, y, z;
    while (m--)
    {
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            scanf("%d%d%d", &x, &y, &z);
            updateRange(x, y, z);
            break;
        case 2:
            scanf("%d%d", &x, &y);
            printf("%d\n", queryRange(x, y));
            break;
        case 3:
            scanf("%d%d", &x, &z);
            update(dfn[x], low[x], 1, n, 1, z);
            break;
        case 4:
            scanf("%d", &x);
            printf("%d\n", query(dfn[x], low[x], 1, n, 1));
            break;
        }
        continue;
    }
    return 0;
}