// CF1264C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 998244353;

int n, pi[MAX_N], prod[MAX_N], q, prefix[MAX_N], sum[MAX_N << 2], mul[MAX_N << 2];
set<int> pts;

int quick_pow(int bas, int tim)
{
    int ret = 1;
    while (tim)
    {
        if (tim & 1)
            ret = 1LL * ret * bas % mod;
        bas = 1LL * bas * bas % mod;
        tim >>= 1;
    }
    return ret;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// segment tree;

void pushup(int p) { sum[p] = 1LL * (1LL * sum[lson] + 1LL * sum[rson]) % mod * mul[p] % mod; }

void pushdown(int p)
{
    if (mul[p] != 1)
    {
        mul[lson] = 1LL * mul[lson] * mul[p] % mod;
        mul[rson] = 1LL * mul[rson] * mul[p] % mod;
        sum[lson] = 1LL * sum[lson] * mul[p] % mod;
        sum[rson] = 1LL * sum[rson] * mul[p] % mod;
        mul[p] = 1;
    }
}

void build(int l, int r, int p)
{
    mul[p] = 1;
    if (l == r)
        return (void)(sum[p] = quick_pow(1LL * prod[n] * quick_pow(prod[l - 1], mod - 2) % mod, mod - 2));
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        sum[p] = 1LL * sum[p] * val % mod, mul[p] = 1LL * mul[p] * val % mod;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int main()
{
    const int inv100 = quick_pow(100, mod - 2);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &pi[i]), pi[i] = 1LL * pi[i] * inv100 % mod;
    for (int i = prod[0] = 1; i <= n; i++)
        prod[i] = 1LL * prod[i - 1] * pi[i] % mod;
    build(1, n, 1);
    pts.insert(1), pts.insert(n + 1);
    while (q--)
    {
        int pt;
        scanf("%d", &pt);
        set<int>::iterator it = pts.lower_bound(pt);
        if (*it == pt)
        {
            // merge to seperate intervals;
            set<int>::iterator lit = it, rit = it;
            lit--, rit++;
            update(*lit, pt - 1, 1, n, 1, quick_pow(1LL * prod[(*rit) - 1] * quick_pow(prod[pt - 1], mod - 2) % mod, mod - 2));
            pts.erase(it);
        }
        else
        {
            // split united interval;
            set<int>::iterator lit = it;
            lit--;
            update(*lit, pt - 1, 1, n, 1, 1LL * prod[(*it) - 1] * quick_pow(prod[pt - 1], mod - 2) % mod);
            pts.insert(pt);
        }
        printf("%d\n", sum[1]);
    }
    return 0;
}