// P2590.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)

typedef long long ll;
using namespace std;

const int MAX_N = 50100, INF = 0x3f3f3f3f;

int head[MAX_N], current, dfn[MAX_N], anti[MAX_N], top[MAX_N];
int fa[MAX_N], son[MAX_N], siz[MAX_N], dep[MAX_N], tot, n;
int tmpx, tmpy, q;
ll sum[MAX_N << 2], mxval[MAX_N << 2];
char opt[20];

struct egde
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void update_sum(int qx, int l, int r, int p, ll val)
{
    if (l == r)
        return (void)(sum[p] = val);
    if (qx <= mid)
        update_sum(qx, l, mid, lson, val);
    else
        update_sum(qx, mid + 1, r, rson, val);
    sum[p] = sum[lson] + sum[rson];
}

void update_mx(int qx, int l, int r, int p, ll val)
{
    if (l == r)
        return (void)(mxval[p] = val);
    if (qx <= mid)
        update_mx(qx, l, mid, lson, val);
    else
        update_mx(qx, mid + 1, r, rson, val);
    mxval[p] = max(mxval[lson], mxval[rson]);
}

ll query_sum(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return sum[p];
    ll ans = 0;
    if (ql <= mid)
        ans += query_sum(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query_sum(ql, qr, mid + 1, r, rson);
    return ans;
}

ll query_mx(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return mxval[p];
    ll ans = -INF;
    if (ql <= mid)
        ans = max(ans, query_mx(ql, qr, l, mid, lson));
    if (mid < qr)
        ans = max(ans, query_mx(ql, qr, mid + 1, r, rson));
    return ans;
}

void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1, son[u] = 0;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to);
            if (siz[edges[i].to] > siz[son[u]])
                son[u] = edges[i].to;
            siz[u] += siz[edges[i].to];
        }
}

void dfs2(int u, int tp)
{
    dfn[u] = ++tot, anti[dfn[u]] = u, top[u] = tp;
    if (son[u])
        dfs2(son[u], tp);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

ll query_sum(int u, int v)
{
    ll ans = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans += query_sum(dfn[top[u]], dfn[u], 1, n, 1);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    ans += query_sum(dfn[u], dfn[v], 1, n, 1);
    return ans;
}

ll query_mx(int u, int v)
{
    ll ans = -INF;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        ans = max(ans, query_mx(dfn[top[u]], dfn[u], 1, n, 1));
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v])
        swap(u, v);
    ans = max(ans, query_mx(dfn[u], dfn[v], 1, n, 1));
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmpx), update_sum(dfn[i], 1, n, 1, tmpx), update_mx(dfn[i], 1, n, 1, tmpx);
    scanf("%d", &q);
    while (q--)
    {
        scanf("%s%d%d", opt, &tmpx, &tmpy);
        switch (opt[1])
        {
        case 'H':
            update_sum(dfn[tmpx], 1, n, 1, tmpy), update_mx(dfn[tmpx], 1, n, 1, tmpy);
            break;
        case 'M':
            printf("%lld\n", query_mx(tmpx, tmpy));
            break;
        case 'S':
            printf("%lld\n", query_sum(tmpx, tmpy));
            break;
        }
    }
    return 0;
}