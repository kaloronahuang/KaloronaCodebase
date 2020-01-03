// UOJ228.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;
typedef long long ll;

int n, m;
ll nodes[MAX_N << 2], max_val[MAX_N << 2], min_val[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p] = nodes[lson] + nodes[rson];
    max_val[p] = max(max_val[lson], max_val[rson]);
    min_val[p] = min(min_val[lson], min_val[rson]);
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(scanf("%lld", &nodes[p]), max_val[p] = min_val[p] = nodes[p]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        nodes[lson] += (mid - l + 1) * tag[p], nodes[rson] += (r - mid) * tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        max_val[lson] += tag[p], max_val[rson] += tag[p];
        min_val[lson] += tag[p], min_val[rson] += tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += (r - l + 1) * val, max_val[p] += val, min_val[p] += val, tag[p] += val);
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void updateSqrt(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr && max_val[p] - (ll)sqrt(max_val[p]) == min_val[p] - (ll)sqrt(min_val[p]))
    {
        ll delta = ((ll)sqrt(max_val[p]) - max_val[p]);
        nodes[p] += (r - l + 1) * delta, max_val[p] += delta, min_val[p] += delta, tag[p] += delta;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        updateSqrt(ql, qr, l, mid, lson);
    if (mid < qr)
        updateSqrt(ql, qr, mid + 1, r, rson);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
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
    build(1, n, 1);
    while (m--)
    {
        int opt, l, r, x;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            scanf("%d", &x), update(l, r, 1, n, 1, x);
        else if (opt == 2)
            updateSqrt(l, r, 1, n, 1);
        else
            printf("%lld\n", query(l, r, 1, n, 1));
    }
    return 0;
}