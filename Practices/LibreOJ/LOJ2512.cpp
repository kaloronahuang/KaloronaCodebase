// P4458.cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, mod = 1e9 + 7, inv2 = 5e8 + 4, inv6 = 166666668;

typedef long long ll;

int n, m, val[MAX_N], pre[MAX_N], nodes[MAX_N << 2], tag[3][MAX_N << 2];

inline char nc()
{
    static char buffer[1 << 20], *p1 = buffer, *p2 = buffer;
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

int read()
{
    int x = 0, f = 1;
    char c = nc();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = nc();
    }
    while (isdigit(c))
        x = (x << 3) + (x << 1) + c - '0', c = nc();
    return x * f;
}

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

// math func;

int pre2(int x) { return 1LL * x * (x + 1) % mod * inv2 % mod; }

int pre3(int x) { return 1LL * x * (x + 1) % mod * (2 * x % mod + 1) % mod * inv6 % mod; }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = pre[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod;
}

void modify(int p, int l, int r, int ca, int cb, int cc)
{
    tag[0][p] = (0LL + tag[0][p] + ca) % mod;
    tag[1][p] = (0LL + tag[1][p] + cb) % mod;
    tag[2][p] = (0LL + tag[2][p] + cc) % mod;
    nodes[p] = (0LL + nodes[p] + 1LL * ca * ((0LL + pre3(r) + mod - pre3(l - 1)) % mod) % mod + 1LL * cb * ((0LL + pre2(r) + mod - pre2(l - 1)) % mod) % mod + 1LL * cc * (r - l + 1) % mod) % mod;
}

void pushdown(int p, int l, int r)
{
    if (tag[0][p] || tag[1][p] || tag[2][p])
    {
        modify(lson, l, mid, tag[0][p], tag[1][p], tag[2][p]);
        modify(rson, mid + 1, r, tag[0][p], tag[1][p], tag[2][p]);
        tag[0][p] = tag[1][p] = tag[2][p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int ca, int cb, int cc)
{
    if (ql <= l && r <= qr)
        return (void)(modify(p, l, r, ca, cb, cc));
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, ca, cb, cc);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, ca, cb, cc);
    nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod;
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    int ret = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ret = (0LL + ret + query(ql, qr, l, mid, lson)) % mod;
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, rson)) % mod;
    return ret;
}

void update(int x, int y, int d)
{
    int len = y - x + 1;
    update(x, y, 0, n, 1, 1LL * d * inv2 % mod, 1LL * d * inv2 % mod * ((3LL + mod - 2LL * x % mod) % mod) % mod, 1LL * (1LL * x * x % mod - 3LL * x % mod + 2) % mod * inv2 % mod * d % mod);
    if (y < n)
        update(y + 1, n, 0, n, 1, 0, 1LL * len * d % mod, (1LL * (len + 1LL) * inv2 % mod + mod - y) % mod * len % mod * d % mod);
}

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        val[i] = read(), pre[i] = (0LL + pre[i - 1] + val[i]) % mod;
    for (int i = 1; i <= n; i++)
        pre[i] = (0LL + pre[i] + pre[i - 1]) % mod;
    build(0, n, 1);
    while (m--)
    {
        int opt, x, y, d;
        opt = read(), x = read(), y = read();
        if (x > y)
            swap(x, y);
        if (opt == 1)
            update(x, y, read());
        else
            printf("%lld\n", (0LL + 1LL * (y - x + 1) * query(n, n, 0, n, 1) % mod + mod - query(n - y, n - x, 0, n, 1) + mod - query(x - 1, y - 1, 0, n, 1)) % mod);
    }
    return 0;
}