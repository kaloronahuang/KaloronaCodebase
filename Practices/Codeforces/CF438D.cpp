// CF438D.cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAX_N = 1e5 + 200;

int n, m, ai[MAX_N];

struct node
{
    ll sum, max_val, min_val, tag;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p].sum = nodes[lson].sum + nodes[rson].sum;
    nodes[p].max_val = max(nodes[lson].max_val, nodes[rson].max_val);
    nodes[p].min_val = min(nodes[lson].min_val, nodes[rson].min_val);
}

void modify(int p, int l, int r, ll val)
{
    nodes[p].tag += val;
    nodes[p].max_val += val, nodes[p].min_val += val;
    nodes[p].sum += (r - l + 1) * val;
}

void pushdown(int p, int l, int r)
{
    if (nodes[p].tag)
    {
        modify(lson, l, mid, nodes[p].tag);
        modify(rson, mid + 1, r, nodes[p].tag);
        nodes[p].tag = 0;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        nodes[p].max_val = nodes[p].min_val = nodes[p].sum = ai[l];
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

ll getK(ll x, ll mod) { return (x - x % mod) / mod; }

void update(int ql, int qr, int l, int r, int p, ll mod)
{
    if (nodes[p].max_val < mod)
        return;
    if (ql <= l && r <= qr && getK(nodes[p].min_val, mod) == getK(nodes[p].max_val, mod))
        return (void)(modify(p, l, r, -getK(nodes[p].min_val, mod) * mod));
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, mod);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, mod);
    pushup(p);
}

void update(int qx, int l, int r, int p, ll val)
{
    if (l == r)
    {
        nodes[p].sum = nodes[p].min_val = nodes[p].max_val = val;
        nodes[p].tag = 0;
        return;
    }
    pushdown(p, l, r);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    pushdown(p, l, r);
    ll ret = 0;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, rson);
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    build(1, n, 1);
    while (m--)
    {
        int opt, l, r, x;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            printf("%lld\n", query(l, r, 1, n, 1));
        else if (opt == 2)
            scanf("%d", &x), update(l, r, 1, n, 1, x);
        else
            update(l, 1, n, 1, r);
    }
    return 0;
}