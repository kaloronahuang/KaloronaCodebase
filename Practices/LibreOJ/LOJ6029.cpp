// LOJ6029.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;
typedef long long ll;
const ll INF = 0x7fffffffffffffff;

ll nodes[MAX_N << 2], max_val[MAX_N << 2], min_val[MAX_N << 2], tag[MAX_N << 2];
int ai[MAX_N], n, q;

ll divide(ll x, ll y) { return x > 0 ? x / y : (x - y + 1) / y; }

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
        return (void)(nodes[p] = max_val[p] = min_val[p] = ai[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void pushdown(int p, int l, int r)
{
    if (tag[p] != 0)
    {
        nodes[lson] += tag[p] * (mid - l + 1), nodes[rson] += tag[p] * (r - mid);
        max_val[lson] += tag[p], max_val[rson] += tag[p];
        min_val[lson] += tag[p], min_val[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += (r - l + 1) * val, tag[p] += val, max_val[p] += val, min_val[p] += val);
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void updateDiv(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr && max_val[p] - divide(max_val[p], val) == min_val[p] - divide(min_val[p], val))
    {
        ll delta = (max_val[p] - divide(max_val[p], val));
        nodes[p] -= (r - l + 1) * delta, tag[p] -= delta, max_val[p] -= delta, min_val[p] -= delta;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        updateDiv(ql, qr, l, mid, lson, val);
    if (mid < qr)
        updateDiv(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

ll querySum(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    ll ret = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ret += querySum(ql, qr, l, mid, lson);
    if (mid < qr)
        ret += querySum(ql, qr, mid + 1, r, rson);
    return ret;
}

ll queryMin(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return min_val[p];
    ll ret = INF;
    pushdown(p, l, r);
    if (ql <= mid)
        ret = min(ret, queryMin(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, queryMin(ql, qr, mid + 1, r, rson));
    return ret;
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    build(1, n, 1);
    while (q--)
    {
        int opt, l, r;
        ll x;
        scanf("%d%d%d", &opt, &l, &r), l++, r++;
        if (opt == 1)
            scanf("%lld", &x), update(l, r, 1, n, 1, x);
        else if (opt == 2)
            scanf("%lld", &x), updateDiv(l, r, 1, n, 1, x);
        else if (opt == 3)
            printf("%lld\n", queryMin(l, r, 1, n, 1));
        else
            printf("%lld\n", querySum(l, r, 1, n, 1));
    }
    return 0;
}