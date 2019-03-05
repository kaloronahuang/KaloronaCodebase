// A.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define ll long long
using namespace std;
const int MAX_N = 1e5 + 2000;
struct node
{
    ll lson, rson, prefix;
} nodes[MAX_N * 20];
ll roots[MAX_N], tot, mapping[MAX_N], arr[MAX_N], n, m, utot;
int build(int l, int r)
{
    int p = ++tot;
    if (l == r)
    {
        nodes[p].prefix = 0;
        return p;
    }
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    nodes[p].prefix = 0;
    return p;
}
int update(int l, int r, int previous, int qx, ll c)
{
    int p = ++tot;
    nodes[p].lson = nodes[previous].lson, nodes[p].rson = nodes[previous].rson;
    nodes[p].prefix = nodes[previous].prefix + c;
    if (l == r && l == qx)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(l, mid, nodes[previous].lson, qx, c);
    else
        nodes[p].rson = update(mid + 1, r, nodes[previous].rson, qx, c);
    return p;
}
ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p].prefix;
    if (mid >= qr)
        return query(ql, qr, l, mid, nodes[p].lson);
    if (mid < ql)
        return query(ql, qr, mid + 1, r, nodes[p].rson);
    return query(ql, qr, l, mid, nodes[p].lson) + query(ql, qr, mid + 1, r, nodes[p].rson);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &arr[i]), mapping[i] = arr[i];
    sort(mapping + 1, mapping + n + 1);
    utot = unique(mapping + 1, mapping + 1 + n) - mapping;
    roots[0] = build(1, n);
    for (int i = 1; i <= n; i++)
    {
        ll val = arr[i], id = lower_bound(mapping + 1, mapping + 1 + utot, val) - mapping;
        roots[i] = update(1, n, roots[i - 1], id, 1);
    }
    while (m--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        ll ans = 0;
        for (int i = l; i <= r; i++)
        {
            ll num = arr[i], id = lower_bound(mapping + 1, mapping + 1 + utot, num) - mapping;
            ans = max(ans, num * (query(id, id, 1, n, roots[r]) - query(id, id, 1, n, roots[l - 1])));
        }
        printf("%lld\n", ans);
    }
    return 0;
}