// CF1217E.cpp
#include <bits/stdc++.h>
#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)
#define ll long long

using namespace std;

const ll MAX_N = 2e5 + 200, INF = 0x3f3f3f3f3f3f3f3f;

struct node
{
    ll digits[11][2];
} nodes[MAX_N << 2];

ll buf[11], n, m, ai[MAX_N];

void calc(ll x)
{
    for (int i = 0; i <= 10; i++)
        buf[i] = x % 10, x /= 10;
}

node merge(node ls, node rs)
{
    node res;
    for (int i = 0; i <= 10; i++)
        res.digits[i][0] = res.digits[i][1] = INF;
    for (int i = 0; i <= 10; i++)
    {
        res.digits[i][0] = min(ls.digits[i][0], rs.digits[i][0]);
        res.digits[i][1] = max(ls.digits[i][0], rs.digits[i][0]);
        res.digits[i][1] = min(res.digits[i][1], ls.digits[i][1]);
        res.digits[i][1] = min(res.digits[i][1], rs.digits[i][1]);
    }
    return res;
}

void build(int l, int r, int p)
{
    if (l == r)
    {
        calc(ai[l]);
        for (int i = 0; i <= 10; i++)
        {
            if (buf[i])
                nodes[p].digits[i][0] = ai[l];
            else
                nodes[p].digits[i][0] = INF;
            nodes[p].digits[i][1] = INF;
        }
        return;
    }
    build(l, mid, lson), build(mid + 1, r, rson);
    nodes[p] = merge(nodes[lson], nodes[rson]);
}

void update(ll pos, int l, int r, int p, ll val)
{
    if (l == r)
    {
        calc(val);
        for (int i = 0; i <= 10; i++)
        {
            if (buf[i])
                nodes[p].digits[i][0] = val;
            else
                nodes[p].digits[i][0] = INF;
            nodes[p].digits[i][1] = INF;
        }
        return;
    }
    if (pos <= mid)
        update(pos, l, mid, lson, val);
    else
        update(pos, mid + 1, r, rson, val);
    nodes[p] = merge(nodes[lson], nodes[rson]);
}

node query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    node res;
    for (int i = 0; i <= 10; i++)
        res.digits[i][0] = res.digits[i][1] = INF;
    if (ql <= mid)
        res = merge(res, query(ql, qr, l, mid, lson));
    if (mid < qr)
        res = merge(res, query(ql, qr, mid + 1, r, rson));
    return res;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &ai[i]);
    build(1, n, 1);
    while (m--)
    {
        ll opt, l, r;
        scanf("%lld%lld%lld", &opt, &l, &r);
        if (opt == 1)
            update(l, 1, n, 1, r);
        else
        {
            node res = query(l, r, 1, n, 1);
            ll ans = INF;
            for (int i = 0; i <= 10; i++)
                ans = min(ans, res.digits[i][0] + res.digits[i][1]);
            if (ans >= INF)
                puts("-1");
            else
                printf("%lld\n", ans);
        }
    }
    return 0;
}