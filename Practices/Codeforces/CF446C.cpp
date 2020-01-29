// CF446C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200, mod = 1e9 + 9;

int n, q, ai[MAX_N], fib[MAX_N];

struct node
{
    int f1, f2, sum, lazy[2];
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int calc1(int x, int y, int len)
{
    if (len == 1)
        return x;
    if (len == 2)
        return y;
    return (1LL * x * fib[len - 2] % mod + 1LL * y * fib[len - 1] % mod) % mod;
}

int calc2(int x, int y, int len)
{
    if (len == 1)
        return x;
    if (len == 2)
        return (0LL + x + y) % mod;
    return (1LL * calc1(x, y, len + 2) + mod - y) % mod;
}

void pushdown(int p, int l, int r)
{
    if (nodes[p].lazy[0])
    {
        nodes[lson].lazy[0] = (1LL * nodes[lson].lazy[0] + nodes[p].lazy[0]) % mod;
        nodes[lson].lazy[1] = (1LL * nodes[lson].lazy[1] + nodes[p].lazy[1]) % mod;
        nodes[lson].sum = (1LL * nodes[lson].sum + calc2(nodes[p].lazy[0], nodes[p].lazy[1], mid - l + 1)) % mod;
        int x = calc1(nodes[p].lazy[0], nodes[p].lazy[1], mid - l + 2), y = calc1(nodes[p].lazy[0], nodes[p].lazy[1], mid - l + 3);
        nodes[rson].lazy[0] = (1LL * nodes[rson].lazy[0] + x) % mod;
        nodes[rson].lazy[1] = (1LL * nodes[rson].lazy[1] + y) % mod;
        nodes[rson].sum = (1LL * nodes[rson].sum + calc2(x, y, r - mid)) % mod;
        nodes[p].lazy[0] = nodes[p].lazy[1] = 0;
    }
}

void pushup(int p) { nodes[p].sum = (1LL * nodes[lson].sum + nodes[rson].sum) % mod; }

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        nodes[p].lazy[0] = (1LL * nodes[p].lazy[0] + fib[l - ql + 1]) % mod;
        nodes[p].lazy[1] = (1LL * nodes[p].lazy[1] + fib[l - ql + 2]) % mod;
        nodes[p].sum = (1LL * nodes[p].sum + calc2(fib[l - ql + 1], fib[l - ql + 2], r - l + 1)) % mod;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ret = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ret = (1LL * ret + query(ql, qr, l, mid, lson)) % mod;
    if (mid < qr)
        ret = (1LL * ret + query(ql, qr, mid + 1, r, rson)) % mod;
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), ai[i] = (1LL * ai[i] + ai[i - 1]) % mod;
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n + 2; i++)
        fib[i] = (1LL * fib[i - 1] + fib[i - 2]) % mod;
    while (q--)
    {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            update(l, r, 1, n, 1);
        else
            printf("%lld\n", ((0LL + ai[r] + mod - ai[l - 1]) % mod + query(l, r, 1, n, 1)) % mod);
    }
    return 0;
}