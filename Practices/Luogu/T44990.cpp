// T44990.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define mid ((l + r) >> 1)
#define ll long long
using namespace std;
const ll maxn = 1000000 + 2000;
ll n, q, xl, xr, sum[maxn << 2], upper[maxn << 2], tag[maxn << 2];
// segment tree;
void pushdown(ll p, ll l, ll r)
{
    if (tag[p] != 0)
    {
        tag[ls] = tag[rs] = tag[p];
        upper[ls] = max(upper[ls], tag[p]);
        upper[rs] = max(upper[rs], tag[p]);
        sum[ls] = 1LL * tag[p] * (mid - l + 1);
        sum[rs] = 1LL * tag[p] * (r - mid);
        tag[p] = 0;
    }
}

void pushup(ll p)
{
    sum[p] = sum[ls] + sum[rs];
    upper[p] = max(upper[ls], upper[rs]);
}

void build(ll l, ll r, ll p)
{
    if (l == r)
    {
        sum[p] = upper[p] = l;
        return;
    }
    build(l, mid, ls);
    build(mid + 1, r, rs);
    pushup(p);
}

void update(ll ql, ll qr, ll l, ll r, ll p, ll c)
{
    if (ql > r || qr < l)
        return;
    if (ql <= l && r <= qr)
    {
        sum[p] = 1LL * (r - l + 1) * c, tag[p] = upper[p] = c;
        return;
    }
    pushdown(p, l, r);
    update(ql, qr, l, mid, ls, c);
    update(ql, qr, mid + 1, r, rs, c);
    pushup(p);
}

ll query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql > r || qr < l)
        return 0;
    if (ql <= l && r <= qr)
        return sum[p];
    pushdown(p, l, r);
    return query(ql, qr, l, mid, ls) + query(ql, qr, mid + 1, r, rs);
}

ll find(ll l, ll r, ll p, ll strd)
{
    if (l == r)
        return l;
    pushdown(p, l, r);
    if (upper[ls] >= strd)
        return find(l, mid, ls, strd);
    else
        return find(mid + 1, r, rs, strd);
}

int main()
{
    scanf("%lld%lld", &n, &q);
    build(0, n, 1);
    ll lastans = 0;
    for (ll i = 0; i < q; i++)
    {
        scanf("%lld%lld", &xl, &xr);
        xl ^= lastans, xr ^= lastans;
        ll pos = find(0, n, 1, xr) - 1;
        if (pos < xl)
            lastans = 0;
        else
        {
            ll res = query(xl, pos, 0, n, 1);
            lastans = 1LL * (pos - xl + 1) * xr - res;
            update(xl, pos, 0, n, 1, xr);
        }
        printf("%lld\n", lastans);
    }
    return 0;
}
