// BZ4725.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 998244353;

int n, q, roots[MAX_N * 21], ptot;

struct node
{
    int lson, rson, val;
} nodes[MAX_N * 402];

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

int fpow(int bas, int tim)
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

int mul(int p, int q) { return (1LL * p * q % mod + ((1LL + mod - p) % mod) * ((1LL + mod - q) % mod) % mod) % mod; }

#define mid ((l + r) >> 1)

int updateY(int ql, int qr, int l, int r, int p, int val)
{
    if (p == 0)
        nodes[p = ++ptot].val = 1;
    if (ql <= l && r <= qr)
        return (nodes[p].val = mul(nodes[p].val, val)), p;
    if (ql <= mid)
        nodes[p].lson = updateY(ql, qr, l, mid, nodes[p].lson, val);
    if (mid < qr)
        nodes[p].rson = updateY(ql, qr, mid + 1, r, nodes[p].rson, val);
    return p;
}

int queryY(int qx, int l, int r, int p)
{
    if (p == 0)
        return 1;
    if (l == r)
        return nodes[p].val;
    if (qx <= mid)
        return mul(queryY(qx, l, mid, nodes[p].lson), nodes[p].val);
    else
        return mul(queryY(qx, mid + 1, r, nodes[p].rson), nodes[p].val);
}

#define lson (p << 1)
#define rson ((p << 1) | 1)

void update(int ql, int qr, int lft, int rig, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(roots[p] = updateY(lft, rig, 1, n, roots[p], val));
    if (ql <= mid)
        update(ql, qr, lft, rig, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, lft, rig, mid + 1, r, rson, val);
}

int query(int qx, int qy, int l, int r, int p)
{
    if (l == r)
        return queryY(qy, 1, n, roots[p]);
    if (qx <= mid)
        return mul(queryY(qy, 1, n, roots[p]), query(qx, qy, l, mid, lson));
    else
        return mul(queryY(qy, 1, n, roots[p]), query(qx, qy, mid + 1, r, rson));
}

int main()
{
    n = read(), q = read();
    while (q--)
    {
        int opt = read(), l = read(), r = read();
        if (opt == 1)
        {
            int inv = fpow(r - l + 1, mod - 2);
            if (l > 1)
                update(1, l - 1, l, r, 0, n, 1, (1 + mod - inv) % mod), update(0, 0, 1, l - 1, 0, n, 1, 0);
            if (r < n)
                update(l, r, r + 1, n, 0, n, 1, (1 + mod - inv) % mod), update(0, 0, r + 1, n, 0, n, 1, 0);
            update(l, r, l, r, 0, n, 1, (1 + mod - 2LL * inv % mod) % mod), update(0, 0, l, r, 0, n, 1, inv);
        }
        else
            printf("%d\n", query(l - 1, r, 0, n, 1));
    }
    return 0;
}