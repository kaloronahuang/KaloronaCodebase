// POJ2482.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define ls (p << 1)
#define rs (ls + 1)
#define mid ((l + r) >> 1)
#define ll long long
using namespace std;
const ll MX_S = 200100;
ll c[MX_S << 2], tag[MX_S << 2], n, W, H, ans;
vector<ll> mapping;
struct quad
{
    ll x, y1, y2, k;
    bool operator<(const quad &qd) const
    {
        if (x == qd.x)
            return k < qd.k;
        return x < qd.x;
    }
};
vector<quad> qds;
ll ripe(ll num) { return lower_bound(mapping.begin(), mapping.end(), num) - mapping.begin(); }
void pushdown(ll p)
{
    if (tag[p])
    {
        c[ls] += tag[p], c[rs] += tag[p];
        tag[ls] += tag[p], tag[rs] += tag[p];
        tag[p] = 0;
    }
}
void update(ll ql, ll qr, ll l, ll r, ll p, ll d)
{
    if (ql <= l && r <= qr)
    {
        c[p] += d, tag[p] += d;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, ls, d);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rs, d);
    c[p] = max(c[ls], c[rs]);
}
int main()
{
    while (scanf("%lld%lld%lld", &n, &W, &H) != EOF)
    {
        ans = -2e9;
        memset(c, 0, sizeof(c)), memset(tag, 0, sizeof(tag));
        qds.clear(), mapping.clear();
        mapping.push_back(-2e9);
        while (n--)
        {
            ll x, y, c;
            scanf("%lld%lld%lld", &x, &y, &c);
            qds.push_back(quad{x, y, y + H - 1, c}), qds.push_back(quad{x + W, y, y + H - 1, -c});
            mapping.push_back(y), mapping.push_back(y + H - 1);
        }
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        ll tot = mapping.size() - 1;
        sort(qds.begin(), qds.end());
        ll siz = qds.size();
        for (ll i = 0; i < siz; i++)
            qds[i].y1 = ripe(qds[i].y1), qds[i].y2 = ripe(qds[i].y2);
        for (ll i = 0; i < siz - 1; i++)
        {
            quad curt = qds[i];
            update(curt.y1, curt.y2, 1, tot, 1, curt.k);
            ans = max(ans, c[1]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}