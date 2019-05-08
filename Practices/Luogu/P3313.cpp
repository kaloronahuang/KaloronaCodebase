// P3313.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;

const int MAX_N = 1e5 + 2000;
int head[MAX_N], current, dfn[MAX_N], tot, anti[MAX_N], dep[MAX_N], fa[MAX_N];
int siz[MAX_N], son[MAX_N], top[MAX_N], colorstat[MAX_N], val[MAX_N], n, q;

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

int roots[MAX_N], ptot;
struct node
{
    int sum, mx, lson, rson;
} nodes[MAX_N * 40];

char opt[20];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1;
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
    dfn[u] = ++tot, anti[dfn[u]] = u, top[u] = org;
    if (son[u] == 0)
        return;
    dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].sum = nodes[p].mx = val;
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    nodes[p].mx = max(nodes[nodes[p].lson].mx, nodes[nodes[p].rson].mx);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
    return p;
}

void remove(int qx, int l, int r, int p)
{
    if (p == 0)
        return;
    if (l == r)
        return (void)(nodes[p].sum = nodes[p].mx = 0);
    if (qx <= mid)
        (remove(qx, l, mid, nodes[p].lson));
    else
        (remove(qx, mid + 1, r, nodes[p].rson));
    nodes[p].mx = max(nodes[nodes[p].lson].mx, nodes[nodes[p].rson].mx);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
}

int query_sum(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ans = 0;
    if (ql <= mid)
        ans += query_sum(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ans += query_sum(ql, qr, mid + 1, r, nodes[p].rson);
    return ans;
}

int query_mx(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].mx;
    int ans = 0;
    if (ql <= mid)
        ans = max(ans, query_mx(ql, qr, l, mid, nodes[p].lson));
    if (mid < qr)
        ans = max(ans, query_mx(ql, qr, mid + 1, r, nodes[p].rson));
    return ans;
}

int query_sum(int x, int y)
{
    int ans = 0, col = colorstat[x];
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans += query_sum(dfn[top[x]], dfn[x], 1, n, roots[col]);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans += query_sum(dfn[x], dfn[y], 1, n, roots[col]);
    return ans;
}

int query_mx(int x, int y)
{
    int ans = 0, col = colorstat[x];
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = max(ans, query_mx(dfn[top[x]], dfn[x], 1, n, roots[col]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans = max(ans, query_mx(dfn[x], dfn[y], 1, n, roots[col]));
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &val[i], &colorstat[i]);
    for (int i = 1, tmpx, tmpy; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        roots[colorstat[i]] = update(dfn[i], 1, n, roots[colorstat[i]], val[i]);
    while (q--)
    {
        int x, y;
        scanf("%s%d%d", opt, &x, &y);
        switch (opt[1])
        {
        case 'C':
            remove(dfn[x], 1, n, roots[colorstat[x]]);
            colorstat[x] = y;
            roots[colorstat[x]] = update(dfn[x], 1, n, roots[colorstat[x]], val[x]);
            break;
        case 'W':
            remove(dfn[x], 1, n, roots[colorstat[x]]);
            val[x] = y;
            roots[colorstat[x]] = update(dfn[x], 1, n, roots[colorstat[x]], val[x]);
            break;
        case 'S':
            printf("%d\n", query_sum(x, y));
            break;
        case 'M':
            printf("%d\n", query_mx(x, y));
            break;
        }
    }
    return 0;
}