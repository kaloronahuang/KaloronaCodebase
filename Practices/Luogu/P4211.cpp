// P4211.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 5e4 + 200, mod = 201314;

int n, q, head[MAX_N], current, fa[MAX_N], dep[MAX_N], siz[MAX_N], top[MAX_N], dfn[MAX_N], ptot, son[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

void dfs1(int u)
{
    dep[u] = dep[fa[u]] + 1, siz[u] = 1;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
    {
        dfs1(edges[i].to), siz[u] += siz[edges[i].to];
        son[u] = siz[edges[i].to] > siz[son[u]] ? edges[i].to : son[u];
    }
}

void dfs2(int u, int org)
{
    dfn[u] = ++ptot, top[u] = org;
    if (son[u])
        dfs2(son[u], org);
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != son[u])
            dfs2(edges[i].to, edges[i].to);
}

namespace PST
{

struct node
{
    int lson, rson, sum, tag;
} nodes[MAX_N * 50];

int stot, roots[MAX_N];

int update(int ql, int qr, int l, int r, int pre, int val)
{
    int p = ++stot;
    nodes[p] = nodes[pre];
    nodes[p].sum = (0LL + nodes[p].sum + 1LL * val * (min(qr, r) - max(ql, l) + 1) % mod) % mod;
    if (ql <= l && r <= qr)
        return (nodes[p].tag = (0LL + nodes[p].tag + val) % mod, p);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson, val);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson, val);
    return p;
}

int query(int ql, int qr, int l, int r, int p, int pre)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return (0LL + nodes[p].sum + mod - nodes[pre].sum) % mod;
    int ret = (1LL * nodes[p].tag * (min(qr, r) - max(ql, l) + 1) % mod - 1LL * nodes[pre].tag * (min(qr, r) - max(ql, l) + 1) % mod + mod) % mod, mid = (l + r) >> 1;
    if (ql <= mid)
        ret = (0LL + ret + query(ql, qr, l, mid, nodes[p].lson, nodes[pre].lson)) % mod;
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, nodes[p].rson, nodes[pre].rson)) % mod;
    return ret;
}

void updateRoot(int ver, int p)
{
    roots[ver] = roots[ver - 1];
    while (p)
        roots[ver] = update(dfn[top[p]], dfn[p], 1, n, roots[ver], 1), p = fa[top[p]];
}

int queryRoot(int L, int R, int p)
{
    int ret = 0;
    while (p)
        ret = (0LL + ret + query(dfn[top[p]], dfn[p], 1, n, roots[R], roots[L - 1])) % mod, p = fa[top[p]];
    return ret;
}

} // namespace PST

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &q);
    for (int i = 2, fat; i <= n; i++)
        scanf("%d", &fat), fat++, addpath(fat, i), fa[i] = fat;
    dfs1(1), dfs2(1, 1);
    for (int i = 1; i <= n; i++)
        PST::updateRoot(i, i);
    while (q--)
    {
        int l, r, z;
        scanf("%d%d%d", &l, &r, &z), l++, r++, z++, printf("%d\n", PST::queryRoot(l, r, z));
    }
    return 0;
}