// LOJ3227.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200;

typedef long long ll;

int n, q, dfn[MAX_N], siz[MAX_N], anti[MAX_N], head[MAX_N], current, ptot;
ll nodes[MAX_N << 2], tag[MAX_N << 2];
set<int> st[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        nodes[lson] += (mid - l + 1) * tag[p], nodes[rson] += (r - mid) * tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p], tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += 1LL * (r - l + 1) * val, tag[p] += val);
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    nodes[p] = nodes[lson] + nodes[rson];
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    ll ret = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs(int u, int fa)
{
    siz[u] = 1, dfn[u] = ++ptot, anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), siz[u] += siz[edges[i].to];
}

void insert(int l, int r, int c)
{
    set<int>::iterator it = st[c].lower_bound(l), rig = st[c].upper_bound(r);
    if (it != st[c].begin())
    {
        it--;
        if (*it + siz[anti[*it]] - 1 >= r)
            return;
        it++;
    }
    while (it != rig)
        update(*it, *it + siz[anti[*it]] - 1, 1, n, 1, -1), st[c].erase(it++);
    update(l, r, 1, n, 1, 1), st[c].insert(l);
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0);
    while (q--)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            scanf("%d", &y), insert(dfn[x], dfn[x] + siz[x] - 1, y);
        else
            printf("%lld\n", query(dfn[x], dfn[x] + siz[x] - 1, 1, n, 1));
    }
    return 0;
}