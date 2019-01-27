// P1502.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define ls (p << 1)
#define rs ((p << 1) | 1)
#define mid ((l + r) >> 1)
#define ll long long
using namespace std;
const ll MAX_N = 30000;
struct node
{
    ll x, y, lit;
};
struct rect
{
    ll x1, y1, y2, val;
    bool operator<(const rect &nd) const { return x1 < nd.x1 || (x1 == nd.x1) && (val < nd.val); }
};
vector<node> pool;
vector<rect> rectpool;
vector<ll> mapping;
ll T, n, W, H, tmpx, tmpy, li, tree[MAX_N << 2], tag[MAX_N << 2];
void update(ll ql, ll qr, ll l, ll r, ll c, ll p)
{
    if (ql <= l && r <= qr)
    {
        tree[p] += c, tag[p] += c;
        return;
    }
    if (tag[p])
    {
        tree[ls] += tag[p], tree[rs] += tag[p];
        tag[ls] += tag[p], tag[rs] += tag[p];
        tag[p] = 0;
    }
    if (ql <= mid)
        update(ql, qr, l, mid, c, ls);
    if (mid < qr)
        update(ql, qr, mid + 1, r, c, rs);
    tree[p] = max(tree[ls], tree[rs]);
}
ll ripe(ll db) { return lower_bound(mapping.begin(), mapping.end(), db) - mapping.begin(); }
int main()
{
    scanf("%lld", &T);
    while (T--)
    {
        mapping.push_back(-2e9);
        scanf("%lld%lld%lld", &n, &W, &H);
        for (ll i = 0; i < n; i++)
        {
            scanf("%lld%lld%lld", &tmpx, &tmpy, &li), pool.push_back(node{tmpx, tmpy, li});
            mapping.push_back(tmpy), mapping.push_back(tmpy + H - 1);
        }
        sort(mapping.begin(), mapping.end());
        mapping.erase(unique(mapping.begin(), mapping.end()), mapping.end());
        ll lst = mapping.size() - 1;
        for (ll i = 0; i < n; i++)
        {
            node nd = pool[i];
            ll x = nd.x, y = nd.y;
            rectpool.push_back(rect{x + W, ripe(y), ripe(y + H - 1), -nd.lit});
            rectpool.push_back(rect{x, ripe(y), ripe(y + H - 1), nd.lit});
        }
        sort(rectpool.begin(), rectpool.end());
        int siz = rectpool.size();
        ll ans = 0;
        for (ll i = 0; i < siz - 1; i++)
        {
            rect rt = rectpool[i];
            update(rt.y1, rt.y2, 1, lst, rt.val, 1);
            ans = max(ans, tree[1]);
        }
        printf("%lld\n", ans);
        pool.clear(), rectpool.clear();
        mapping.clear(), memset(tree, 0, sizeof(tree)), memset(tag, 0, sizeof(tag));
    }
    return 0;
}