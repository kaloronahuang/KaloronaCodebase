// B.cpp
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

using namespace std;

const int MAX_N = 31000;

int head[MAX_N], current, pt_weight[MAX_N], dfn[MAX_N], antidfn[MAX_N], m;
int top[MAX_N], son[MAX_N], siz[MAX_N], dep[MAX_N], fa[MAX_N], dfntot, n, opt;

int tree[MAX_N << 2];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(tree[p] = pt_weight[antidfn[l]]);
    build(l, mid, lson), build(mid + 1, r, rson);
    tree[p] = tree[lson] + tree[rson];
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r && qx == l)
        return (void)(tree[p] = val);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    tree[p] = tree[lson] + tree[rson];
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}

int query(int x, int y)
{
    if (dep[top[x]] > dep[top[y]])
        swap(x, y);
    int ans = 0;
    while (top[x] != top[y])
    {
        ans += query(dfn[top[y]], dfn[y], 1, n, 1);
        y = fa[top[y]];
        if (dep[top[x]] > dep[top[y]])
            swap(x, y);
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans += query(dfn[x], dfn[y], 1, n, 1);
    return ans;
}

void dfs1(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to);
            siz[u] += siz[edges[i].to];
            if (siz[edges[i].to] > siz[son[u]])
                son[u] = edges[i].to;
        }
}

void dfs2(int u, int org)
{
    dfn[u] = ++dfntot, antidfn[dfntot] = u, top[u] = org;
    if (son[u] == 0)
        return;
    dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pt_weight[i]);
    build(1, n, 1);
    while (m--)
    {
        int A, B;
        scanf("%d%d%d", &opt, &A, &B);
        if (opt == 1)
            update(dfn[A], 1, n, 1, B);
        else 
            printf("%d\n", query(A, B));
    }
    return 0;
}