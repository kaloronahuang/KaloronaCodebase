// B.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int MAX_N = 100010;

ll n, q, mod;
ll nodes[MAX_N << 2], tag_delta[MAX_N << 2], tag_prod[MAX_N << 2], seq[MAX_N];

#define lson (p << 1)
#define rson (lson | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p] = (1LL * nodes[lson] + 1LL * nodes[rson]) % mod;
}

void pushdown(int l, int r, int p)
{
    if (tag_prod[p] == 1 && tag_delta[p] == 0)
        return;
    tag_delta[lson] = (1LL * tag_delta[lson] * tag_prod[p] + 1LL * tag_delta[p]) % mod;
    tag_prod[lson] = 1LL * tag_prod[lson] * tag_prod[p] % mod;
    nodes[lson] = (1LL * nodes[lson] * tag_prod[p] % mod + 1LL * tag_delta[p] * (mid - l + 1)) % mod;

    tag_delta[rson] = (1LL * tag_delta[rson] * tag_prod[p] + 1LL * tag_delta[p]) % mod;
    tag_prod[rson] = 1LL * tag_prod[rson] * tag_prod[p] % mod;
    nodes[rson] = (1LL * nodes[rson] * tag_prod[p] % mod + 1LL * tag_delta[p] * (r - mid)) % mod;

    tag_prod[p] = 1, tag_delta[p] = 0;
}

void build(int l, int r, int p)
{
    tag_prod[p] = 1;
    if (l == r)
        return (void)(nodes[p] = seq[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, ll delta, ll prod)
{
    if (ql <= l && r <= qr)
    {
        if (delta == 0)
            tag_delta[p] = 1LL * tag_delta[p] * prod % mod;
        nodes[p] = ((1LL * nodes[p] + 1LL * (r - l + 1) * delta % mod) % mod) * prod % mod;
        tag_prod[p] = 1LL * tag_prod[p] * prod % mod;
        tag_delta[p] = (1LL * tag_delta[p] + delta) % mod;
        return;
    }
    pushdown(l, r, p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, delta, prod);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, delta, prod);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p] % mod;
    ll ans = 0;
    pushdown(l, r, p);
    if (ql <= mid)
        ans = (1LL * ans + query(ql, qr, l, mid, lson)) % mod;
    if (mid < qr)
        ans = (1LL * ans + query(ql, qr, mid + 1, r, rson)) % mod;
    return ans;
}

int main()
{
    scanf("%lld%lld", &n, &mod);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    build(1, n, 1), scanf("%d", &q);
    while (q--)
    {
        ll op, l, r, tmp;
        scanf("%lld%lld%lld", &op, &l, &r);
        if (op == 1)
            scanf("%lld", &tmp), update(l, r, 1, n, 1, 0, tmp);
        else if (op == 2)
            scanf("%lld", &tmp), update(l, r, 1, n, 1, tmp, 1);
        else
            printf("%lld\n", query(l, r, 1, n, 1));
    }
    return 0;
}