// CH4302.cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#define ls (p << 1)
#define rs ((p << 1) + 1)
#define mid ((l + r) >> 1)
#define lowbit(num) (num & -num)
#define ll long long
using namespace std;
const ll maxn = 500030;
ll N, M, arr[maxn], tree[maxn << 2], dsum[maxn], bst[maxn];
ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}
void build(ll l, ll r, ll p)
{
    if (l == r)
    {
        tree[p] = dsum[l];
        return;
    }
    build(l, mid, ls);
    build(mid + 1, r, rs);
    tree[p] = gcd(tree[ls], tree[rs]);
}
void update(ll pt, ll l, ll r, ll p, ll val)
{
    if (l == r)
    {
        tree[p] += val;
        return;
    }
    if (pt <= mid)
        update(pt, l, mid, ls, val);
    else
        update(pt, mid + 1, r, rs, val);
    tree[p] = gcd(tree[ls], tree[rs]);
}
ll query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql <= l && r <= qr)
        return abs(tree[p]);
    ll res = 0;
    if (ql <= mid)
        res = gcd(res, query(ql, qr, l, mid, ls));
    if (mid < qr)
        res = gcd(res, query(ql, qr, mid + 1, r, rs));
    return abs(res);
}

void add(ll x, ll d)
{
    while (x <= N)
        bst[x] += d, x += lowbit(x);
}
ll sum(ll x)
{
    ll res = 0;
    while (x > 0)
        res += bst[x], x -= lowbit(x);
    return res;
}
int main()
{
    scanf("%lld%lld", &N, &M);
    for (ll i = 1; i <= N; i++)
        scanf("%lld", &arr[i]), dsum[i] = arr[i] - arr[i - 1];
    build(1, N, 1);
    while (M--)
    {
        char opt[2];
        ll a, b, c;
        scanf("%s%lld%lld", opt, &a, &b);
        if (opt[0] == 'Q')
        {
            ll pnum = arr[a] + sum(a);
            ll anum = a < b ? query(a + 1, b, 1, N, 1) : 0;
            printf("%lld\n", gcd(anum, pnum));
        }
        else
        {
            scanf("%lld", &c);
            update(a, 1, N, 1, c);
            if (b < N)
                update(b + 1, 1, N, 1, -c);
            add(a, c), add(b + 1, -c);
        }
    }
    return 0;
}