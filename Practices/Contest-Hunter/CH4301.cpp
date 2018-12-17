// CH4301.cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ls (p << 1)
#define rs ((p << 1) + 1)
#define mid ((l + r) >> 1)
#define ll long long
using namespace std;
const ll maxn = 500200, ninf = -2e9;
ll arr[maxn], n, m;
struct node
{
    ll sum, lsum, rsum, maxsum;
    node(ll tmp = 0)
    {
        sum = lsum = rsum = maxsum = tmp;
    }
} nodes[maxn << 3];
void pushup(ll p)
{
    nodes[p].sum = nodes[ls].sum + nodes[rs].sum;
    nodes[p].maxsum = max(max(nodes[ls].maxsum, nodes[rs].maxsum), nodes[rs].lsum + nodes[ls].rsum);
    nodes[p].lsum = max(nodes[ls].lsum, nodes[ls].sum + nodes[rs].lsum);
    nodes[p].rsum = max(nodes[rs].rsum, nodes[rs].sum + nodes[ls].rsum);
}
void build(ll l, ll r, ll p)
{

    nodes[p] = node(arr[l]);
    if (l == r)
        return;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    pushup(p);
}
void update(ll ql, ll qr, ll l, ll r, ll p, ll val)
{
    if (l == r)
    {
        arr[l] = val;
        nodes[p].sum = nodes[p].rsum = nodes[p].maxsum = nodes[p].lsum = val;
        return;
    }
    if (ql <= mid)
        update(ql, qr, l, mid, ls, val);
    else
        update(ql, qr, mid + 1, r, rs, val);
    pushup(p);
}
node query(ll ql, ll qr, ll l, ll r, ll p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    node res, lft(ninf), rig(ninf);
    res.sum = 0;
    if (ql <= mid)
        lft = query(ql, qr, l, mid, ls), res.sum += lft.sum;
    if (mid < qr)
        rig = query(ql, qr, mid + 1, r, rs), res.sum += rig.sum;
    res.maxsum = max(lft.rsum + rig.lsum, max(lft.maxsum, rig.maxsum));
    res.lsum = max(lft.lsum, lft.sum + rig.lsum);
    if (ql > mid)
        res.lsum = max(rig.lsum, res.lsum);
    res.rsum = max(rig.rsum, lft.rsum + rig.sum);
    if (qr <= mid)
        res.rsum = max(lft.rsum, res.rsum);
    return res;
}
int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        scanf("%lld", &arr[i]);
    build(1, n, 1);
    while (m--)
    {
        ll opt, a, b;
        scanf("%lld%lld%lld", &opt, &a, &b);
        if (opt == 1)
        {
            if (a > b)
                swap(a, b);
            printf("%lld\n", query(a, b, 1, n, 1).maxsum);
        }
        else
            update(a, a, 1, n, 1, b);
    }
    return 0;
}