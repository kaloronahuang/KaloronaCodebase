// LOJ3043.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

typedef long long ll;

int n, q, T = 1;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int f[MAX_N << 2], g[MAX_N << 2], fsum[MAX_N << 2], tagf[MAX_N << 2], tagg[MAX_N << 2];

void pushup(int p) { fsum[p] = (0LL + f[p] + fsum[lson] + fsum[rson]) % mod; }

void modifyF(int p, int val) { f[p] = 1LL * f[p] * val % mod, tagf[p] = 1LL * tagf[p] * val % mod, fsum[p] = 1LL * fsum[p] * val % mod; }

void modifyG(int p, int val) { g[p] = 1LL * g[p] * val % mod, tagg[p] = 1LL * tagg[p] * val % mod; }

void pushdown(int p)
{
    if (tagf[p] != 1)
        modifyF(lson, tagf[p]), modifyF(rson, tagf[p]), tagf[p] = 1;
    if (tagg[p] != 1)
        modifyG(lson, tagg[p]), modifyG(rson, tagg[p]), tagg[p] = 1;
}

void build(int l, int r, int p)
{
    g[p] = tagf[p] = tagg[p] = 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

void update(int ql, int qr, int l, int r, int p)
{
    pushdown(p);
    if (ql == l && r == qr)
    {
        f[p] = (0LL + f[p] + T) % mod;
        modifyF(lson, 2), modifyF(rson, 2);
        pushup(p);
        return;
    }
    g[p] = (0LL + g[p] + T) % mod;
    if (qr <= mid)
    {
        // lson;
        update(ql, qr, l, mid, lson), pushdown(rson);
        f[rson] = (0LL + f[rson] + T + mod - g[rson]) % mod, g[rson] = (0LL + g[rson] + g[rson]) % mod;
        modifyF(rson << 1, 2), modifyF(rson << 1 | 1, 2);
        modifyG(rson << 1, 2), modifyG(rson << 1 | 1, 2);
        pushup(rson);
    }
    else if (ql > mid)
    {
        // rson;
        update(ql, qr, mid + 1, r, rson), pushdown(lson);
        f[lson] = (0LL + f[lson] + T + mod - g[lson]) % mod, g[lson] = (0LL + g[lson] + g[lson]) % mod;
        modifyF(lson << 1, 2), modifyF(lson << 1 | 1, 2);
        modifyG(lson << 1, 2), modifyG(lson << 1 | 1, 2);
        pushup(lson);
    }
    else
        update(ql, mid, l, mid, lson), update(mid + 1, qr, mid + 1, r, rson);
    pushup(p);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q), build(1, n, 1);
    while (q--)
    {
        int opt, l, r;
        scanf("%d", &opt);
        if (opt == 2)
            printf("%d\n", fsum[1]);
        else
            scanf("%d%d", &l, &r), update(l, r, 1, n, 1), T = (T + T) % mod;
    }
    return 0;
}