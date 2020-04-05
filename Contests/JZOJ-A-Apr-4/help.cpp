// help.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, MAX_K = 11, mod = 1e9 + 7;

int n, idx, nodes[MAX_N << 2][MAX_K], tag[MAX_N << 2], S[MAX_K][MAX_K], tmp[MAX_K], f[MAX_K];

struct segment
{
    int l, r;
    bool operator<(const segment &rhs) const { return l < rhs.l; }
} segs[MAX_N];

void fileIO()
{
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void updateTag(int p, int val)
{
    for (int i = 0; i <= idx; i++)
        nodes[p][i] = 1LL * nodes[p][i] * val % mod;
    tag[p] = 1LL * tag[p] * val % mod;
}

void pushdown(int p)
{
    if (tag[p] != 1)
    {
        updateTag(lson, tag[p]), updateTag(rson, tag[p]);
        tag[p] = 1;
    }
}

void pushup(int p)
{
    for (int i = 0; i <= idx; i++)
        nodes[p][i] = (0LL + nodes[lson][i] + nodes[rson][i]) % mod;
}

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return (void)(updateTag(p, 2));
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    pushup(p);
}

void updateSum(int qx, int l, int r, int p, int *val)
{
    for (int i = 0; i <= idx; i++)
        nodes[p][i] = (0LL + nodes[p][i] + val[i]) % mod;
    if (l == r)
        return;
    pushdown(p);
    if (qx <= mid)
        updateSum(qx, l, mid, lson, val);
    else
        updateSum(qx, mid + 1, r, rson, val);
}

void query(int *ret, int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        for (int i = 0; i <= idx; i++)
            ret[i] = (0LL + ret[i] + nodes[p][i]) % mod;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        query(ret, ql, qr, l, mid, lson);
    if (mid < qr)
        query(ret, ql, qr, mid + 1, r, rson);
}

void build(int l, int r, int p)
{
    tag[p] = 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &idx);
    S[0][0] = 1, build(0, n << 1, 1);
    for (int i = 1; i <= idx; i++)
    {
        S[i][i] = 1;
        for (int j = 1; j < i; j++)
            S[i][j] = (0LL + 1LL * S[i - 1][j] * j + S[i - 1][j - 1]) % mod;
    }
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segs[i].l, &segs[i].r);
    sort(segs + 1, segs + 1 + n), tmp[0] = 1;
    updateSum(0, 0, n << 1, 1, tmp);
    for (int i = 1; i <= n; i++)
    {
        memset(tmp, 0, sizeof(tmp)), query(tmp, 0, segs[i].l - 1, 0, n << 1, 1), f[0] = tmp[0];
        for (int j = 1; j <= idx; j++)
            f[j] = (0LL + tmp[j] + tmp[j - 1]) % mod;
        memset(tmp, 0, sizeof(tmp)), query(tmp, segs[i].l, segs[i].r, 0, n << 1, 1);
        for (int j = 0; j <= idx; j++)
            f[j] = (0LL + f[j] + tmp[j]) % mod;
        update(segs[i].r + 1, n << 1, 0, n << 1, 1);
        updateSum(segs[i].r, 0, n << 1, 1, f);
    }
    int ans = 0;
    // Stiring Number;
    // Yali Training 2018.1.6, DAG.
    for (int i = 0, fac = 1; i <= idx; i++, fac = 1LL * fac * i % mod)
        ans = (0LL + ans + 1LL * fac * S[idx][i] % mod * nodes[1][i] % mod) % mod;
    printf("%d\n", ans);
    return 0;
}