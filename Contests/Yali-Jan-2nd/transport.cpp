// transport.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 2000, mod = 1e9 + 7;

int n, m, head[MAX_N], current, lft[MAX_N], rig[MAX_N], val[MAX_N], ptot, dep[MAX_N];
int siz[MAX_N], sol[MAX_N], anti[MAX_N], I[MAX_N];

struct edge
{
    int to, nxt;
} edges[MAX_N << 1];

void addpath(int src, int dst)
{
    edges[current].to = dst, edges[current].nxt = head[src];
    head[src] = current++;
}

struct segmentTree
{
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

    int nodes[MAX_N << 2], tag[MAX_N << 2], coeff[MAX_N << 2];

    void pushdown(int p)
    {
        if (tag[p])
        {
            tag[lson] = (1LL * tag[lson] + 1LL * tag[p]) % mod, tag[rson] = (1LL * tag[rson] + 1LL * tag[p]) % mod;
            nodes[lson] = (1LL * nodes[lson] + 1LL * coeff[lson] * tag[p] % mod) % mod;
            nodes[rson] = (1LL * nodes[rson] + 1LL * coeff[rson] * tag[p] % mod) % mod;
            tag[p] = 0;
        }
    }

    void pushup(int p) { return (void)(nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod); }

    void build(int l, int r, int p, int *cf, int *solid)
    {
        if (l == r)
        {
            nodes[p] = 1LL * cf[anti[l]] * solid[anti[l]] % mod;
            coeff[p] = cf[anti[l]];
            return;
        }
        build(l, mid, lson, cf, solid), build(mid + 1, r, rson, cf, solid);
        pushup(p), coeff[p] = (0LL + mod + (0LL + coeff[lson] + coeff[rson]) % mod) % mod;
        return;
    }

    void update(int ql, int qr, int l, int r, int p, int val)
    {
        if (ql <= l && r <= qr)
        {
            tag[p] = (1LL * tag[p] + mod + val) % mod;
            nodes[p] = (1LL * nodes[p] + mod + 1LL * val * coeff[p] % mod) % mod;
            return;
        }
        pushdown(p);
        if (ql <= mid)
            update(ql, qr, l, mid, lson, val);
        if (mid < qr)
            update(ql, qr, mid + 1, r, rson, val);
        pushup(p);
    }

    int query(int ql, int qr, int l, int r, int p)
    {
        if (ql <= l && r <= qr)
            return nodes[p];
        pushdown(p);
        int ret = 0;
        if (ql <= mid)
            ret = (1LL * ret + query(ql, qr, l, mid, lson)) % mod;
        if (mid < qr)
            ret = (1LL * ret + query(ql, qr, mid + 1, r, rson)) % mod;
        return ret;
    }

#undef mid
#undef rson
#undef lson
} seg1, seg2, seg3;

void dfs(int u, int fa)
{
    lft[u] = ++ptot, dep[u] = dep[fa] + 1, siz[u] = 1, sol[u] = 1;
    anti[ptot] = u;
    for (int i = head[u]; i != -1; i = edges[i].nxt)
        if (edges[i].to != fa)
            dfs(edges[i].to, u), sol[u] = (1LL * sol[u] + 1LL * siz[u] * siz[edges[i].to]) % mod, siz[u] += siz[edges[i].to];
    rig[u] = ptot;
}

int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= n - 1; i++)
        scanf("%d%d", &u, &v), addpath(u, v), addpath(v, u);
    dfs(1, 0), fill(I, I + MAX_N, 1);
    seg1.build(1, n, 1, I, dep), seg2.build(1, n, 1, sol, dep), seg3.build(1, n, 1, sol, I);
    while (m--)
    {
        int opt, l, r;
        scanf("%d%d", &opt, &l);
        if (opt == 1)
        {
            scanf("%d", &r);
            seg1.update(lft[l], rig[l], 1, n, 1, r);
            seg2.update(lft[l], rig[l], 1, n, 1, r);
            seg3.update(lft[l], lft[l], 1, n, 1, r);
        }
        else
        {
            long long ans = 1LL * seg1.query(lft[l], rig[l], 1, n, 1) * (siz[l] + 1) % mod;
            ans = (ans + mod - 2LL * seg2.query(lft[l], rig[l], 1, n, 1) % mod) % mod;
            ans = (ans + 1LL * seg3.query(lft[l], rig[l], 1, n, 1) % mod) % mod;
            printf("%lld\n", ans);
        }
    }
    return 0;
}