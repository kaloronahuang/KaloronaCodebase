// P2486.cpp
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)
using namespace std;

const int MAX_N = 1e5 + 2000;
int head[MAX_N], current, dfn[MAX_N], son[MAX_N], siz[MAX_N], tot, anti[MAX_N];
int fa[MAX_N], dep[MAX_N], org[MAX_N], n, q, source[MAX_N];
char opt[20];
struct edge
{
    int to, nxt;
} edges[MAX_N << 1];
struct node
{
    int sum, tag, lft_color, rig_color;
} nodes[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs1(int u)
{
    siz[u] = 1, dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to);
            siz[u] += siz[edges[i].to];
            if (siz[son[u]] < siz[edges[i].to])
                son[u] = edges[i].to;
        }
}

void dfs2(int u, int top)
{
    org[u] = top, dfn[u] = ++tot, anti[tot] = u;
    if (son[u] == 0)
        return;
    dfs2(son[u], top);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u] && edges[i].to != fa[u])
            dfs2(edges[i].to, edges[i].to);
}

void pushdown(int p)
{
    if (nodes[p].tag)
    {
        nodes[lson].tag = nodes[rson].tag = 1;
        nodes[lson].sum = nodes[rson].sum = 1;
        nodes[lson].lft_color = nodes[lson].rig_color = nodes[p].lft_color;
        nodes[rson].lft_color = nodes[rson].rig_color = nodes[p].rig_color;
        nodes[p].tag = 0;
    }
}

void pushup(int p)
{
    nodes[p].lft_color = nodes[lson].lft_color, nodes[p].rig_color = nodes[rson].rig_color;
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum;
    if (nodes[lson].rig_color == nodes[rson].lft_color)
        nodes[p].sum--;
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql == l && r == qr)
    {
        nodes[p].lft_color = nodes[p].rig_color = val;
        nodes[p].sum = nodes[p].tag = 1;
        return;
    }
    pushdown(p);
    if (qr <= mid)
        update(ql, qr, l, mid, lson, val);
    else if (ql > mid)
        update(ql, qr, mid + 1, r, rson, val);
    else
        update(ql, mid, l, mid, lson, val), update(mid + 1, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p, int QL, int QR, int &lft, int &rig)
{
    if (l == QL)
        lft = nodes[p].lft_color;
    if (r == QR)
        rig = nodes[p].rig_color;
    if (ql == l && r == qr)
        return nodes[p].sum;
    pushdown(p);
    if (qr <= mid)
        return query(ql, qr, l, mid, lson, QL, QR, lft, rig);
    else if (ql > mid)
        return query(ql, qr, mid + 1, r, rson, QL, QR, lft, rig);
    else
        return query(ql, mid, l, mid, lson, QL, QR, lft, rig) + query(mid + 1, qr, mid + 1, r, rson, QL, QR, lft, rig) -
               (nodes[lson].rig_color == nodes[rson].lft_color ? 1 : 0);
}

void update(int x, int y, int c)
{
    while (org[x] != org[y])
    {
        if (dep[org[x]] < dep[org[y]])
            swap(x, y);
        update(dfn[org[x]], dfn[x], 1, n, 1, c);
        x = fa[org[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    update(dfn[x], dfn[y], 1, n, 1, c);
}

int query(int x, int y)
{
    int ans = 0, last1 = -1, last2 = -1, lcol, rcol;
    while (org[x] != org[y])
    {
        if (dep[org[x]] < dep[org[y]])
            swap(x, y), swap(last1, last2);
        ans += query(dfn[org[x]], dfn[x], 1, n, 1, dfn[org[x]], dfn[x], lcol, rcol);
        if (rcol == last1)
            ans--;
        last1 = lcol;
        x = fa[org[x]];
    }
    if (dep[x] < dep[y])
        swap(x, y), swap(last1, last2);
    ans += query(dfn[y], dfn[x], 1, n, 1, dfn[y], dfn[x], lcol, rcol);
    if (rcol == last1)
        ans--;
    if (lcol == last2)
        ans--;
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &source[i]);
    for (int i = 1, tmpx, tmpy; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        update(dfn[i], dfn[i], 1, n, 1, source[i]);
    while (q--)
    {
        int x, y, c;
        scanf("%s", opt);
        switch (opt[0])
        {
        case 'C':
            scanf("%d%d%d", &x, &y, &c);
            update(x, y, c);
            break;
        case 'Q':
            scanf("%d%d", &x, &y), printf("%d\n", query(x, y));
            break;
        }
    }
    return 0;
}