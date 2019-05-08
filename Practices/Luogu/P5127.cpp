// P5127.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;

const int MAX_N = 200100, mod = 1e9 + 7;

int head[MAX_N], current, source[MAX_N];
int dfn[MAX_N], dep[MAX_N], fa[MAX_N], anti[MAX_N], tot, top[MAX_N];
int son[MAX_N], siz[MAX_N], n, m, power2[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

unsigned orsum[MAX_N << 2], andsum[MAX_N << 2], tag[MAX_N << 2];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void edit(int p, unsigned c)
{
    unsigned A = orsum[p], B = andsum[p];
    orsum[p] = (A & ~c) | (c & ~B);
    andsum[p] = (B & ~c) | (c & ~A);
    tag[p] ^= c;
}

void pushdown(int p)
{
    if (tag[p])
    {
        edit(lson, tag[p]), edit(rson, tag[p]);
        tag[p] = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(andsum[p] = orsum[p] = source[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    orsum[p] = orsum[lson] | orsum[rson];
    andsum[p] = andsum[lson] & andsum[rson];
}

void update(int ql, int qr, int l, int r, int p, unsigned val)
{
    if (ql <= l && r <= qr)
        return (void)(edit(p, val));
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    orsum[p] = orsum[lson] | orsum[rson];
    andsum[p] = andsum[lson] & andsum[rson];
}

unsigned query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return orsum[p];
    pushdown(p);
    unsigned ans = 0;
    if (ql <= mid)
        ans |= query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans |= query(ql, qr, mid + 1, r, rson);
    return ans;
}

void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u])
        {
            fa[edges[i].to] = u, dfs1(edges[i].to);
            siz[u] += siz[edges[i].to];
            if (siz[son[u]] < siz[edges[i].to])
                son[u] = edges[i].to;
        }
}

void dfs2(int u, int org)
{
    dfn[u] = ++tot, anti[tot] = u, top[u] = org;
    if (son[u] == 0)
        return;
    dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa[u] && edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

void update(int x, int y, unsigned c)
{
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

int query(int x, int y)
{
    unsigned ans = 0, cnt = 0;
    while (top[x] != top[y])
    {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans |= query(dfn[top[x]], dfn[x], 1, n, 1);
        cnt += dfn[x] - dfn[top[x]] + 1;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        swap(x, y);
    ans |= query(dfn[x], dfn[y], 1, n, 1);
    cnt += dfn[y] - dfn[x] + 1;
    return 1LL * power2[cnt - 1] % mod * ans % mod;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, tmpx, tmpy; i <= n - 1; i++)
        scanf("%d%d", &tmpx, &tmpy), addpath(tmpx, tmpy), addpath(tmpy, tmpx);
    dfs1(1), dfs2(1, 1), power2[0] = 1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &source[dfn[i]]), power2[i] = (power2[i - 1] << 1) % mod;
    build(1, n, 1);
    while (m--)
    {
        int opt, x, y;
        unsigned c;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            printf("%d\n", query(x, y));
        else
            scanf("%u", &c), update(x, y, c);
    }
    return 0;
}