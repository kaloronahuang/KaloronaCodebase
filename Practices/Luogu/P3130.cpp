// P3130.cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAX_N = 2e5 + 200;

ll n, m, seq[MAX_N], tag[MAX_N << 2], sum[MAX_N << 2], min_val[MAX_N << 2], q;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        sum[lson] += (mid - l + 1) * tag[p];
        sum[rson] += (r - mid) * tag[p];
        min_val[lson] += tag[p], min_val[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { sum[p] = sum[lson] + sum[rson], min_val[p] = min(min_val[lson], min_val[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(sum[p] = min_val[p] = seq[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, ll val)
{
    if (ql <= l && r <= qr)
    {
        sum[p] += (r - l + 1) * val;
        min_val[p] += val;
        tag[p] += val;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

ll query_sum(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return sum[p];
    ll ans = 0;
    pushdown(p, l, r);
    if (ql <= mid)
        ans += query_sum(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query_sum(ql, qr, mid + 1, r, rson);
    return ans;
}

ll query_min(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return min_val[p];
    ll ans = 0x7fffffffffffffff;
    pushdown(p, l, r);
    if (ql <= mid)
        ans = min(ans, query_min(ql, qr, l, mid, lson));
    if (mid < qr)
        ans = min(ans, query_min(ql, qr, mid + 1, r, rson));
    return ans;
}

int main()
{
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    build(1, n, 1);
    while (q--)
    {
        char opt[4];
        scanf("%s", opt + 1);
        ll l, r, v;
        if (opt[1] == 'M')
            scanf("%lld%lld", &l, &r), printf("%lld\n", query_min(l, r, 1, n, 1));
        else if (opt[1] == 'P')
            scanf("%lld%lld%lld", &l, &r, &v), update(l, r, 1, n, 1, v);
        else
            scanf("%lld%lld", &l, &r), printf("%lld\n", query_sum(l, r, 1, n, 1));
    }
    return 0;
}