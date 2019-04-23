// P2221.cpp
#include <bits/stdc++.h>
#define ll long long
#define lson (p << 1)
#define rson ((p << 1) | 1)
using namespace std;

const ll MAX_N = 101000;

ll tree[6][MAX_N << 2], tag[MAX_N << 2];
ll sum1, sum2, sum3, n, m;

inline ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

void build(ll l, ll r, ll p)
{
    if (l == r)
    {
        tree[4][p] = l * l, tree[5][p] = l;
        return;
    }
    ll mid = (l + r) >> 1;
    build(l, mid, lson), build(mid + 1, r, rson);
    tree[4][p] = tree[4][lson] + tree[4][rson];
    tree[5][p] = tree[5][lson] + tree[5][rson];
}

void setVar(ll l, ll r, ll p, ll val)
{
    tree[1][p] += (r - l + 1) * val;
    tree[2][p] += val * tree[5][p];
    tree[3][p] += val * tree[4][p];
    tag[p] += val;
}

void pushdown(ll l, ll r, ll p)
{
    ll mid = (l + r) >> 1;
    setVar(l, mid, lson, tag[p]), setVar(mid + 1, r, rson, tag[p]);
    tag[p] = 0;
}

void update(ll ql, ll qr, ll l, ll r, ll p, ll val)
{
    if (ql <= l && r <= qr)
    {
        setVar(l, r, p, val);
        return;
    }
    ll mid = (l + r) >> 1;
    if (tag[p])
        pushdown(l, r, p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);

    tree[1][p] = tree[1][lson] + tree[1][rson];
    tree[2][p] = tree[2][lson] + tree[2][rson];
    tree[3][p] = tree[3][lson] + tree[3][rson];
}

void query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql <= l && r <= qr)
    {
        sum1 += tree[1][p];
        sum2 += tree[2][p];
        sum3 += tree[3][p];
        return;
    }
    ll mid = (l + r) >> 1;
    if (tag[p])
        pushdown(l, r, p);
    if (ql <= mid)
        query(ql, qr, l, mid, lson);
    if (mid < qr)
        query(ql, qr, mid + 1, r, rson);
    return;
}

signed main()
{
    ll lft, rig, val;
    char opt[3];
    scanf("%lld%lld", &n, &m);
    build(1, n, 1);
    while (m--)
    {
        scanf("%s", opt);
        lft = read(), rig = read() - 1;
        if (opt[0] == 'C')
            scanf("%lld", &val), update(lft, rig, 1, n, 1, val);
        else
        {
            sum1 = sum2 = sum3 = 0;
            query(lft, rig, 1, n, 1);
            ll upper = (rig - lft + 1 - rig * lft) * sum1 + (rig + lft) * sum2 - sum3;
            ll lower = (rig - lft + 2) * (rig - lft + 1) / 2;
            ll g = gcd(upper, lower);
            printf("%lld/%lld\n", upper / g, lower / g);
        }
    }
    return 0;
}