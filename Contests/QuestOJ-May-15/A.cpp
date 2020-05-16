// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, mod = 1e9 + 9;

typedef pair<int, int> pii;

int n, m, xi[MAX_N], nodes[MAX_N << 2], tagMul[MAX_N << 2], tagAdd[MAX_N << 2];
pii segs[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void modifyMul(int p, int mul)
{
    nodes[p] = 1LL * nodes[p] * mul % mod;
    tagAdd[p] = 1LL * tagAdd[p] * mul % mod;
    tagMul[p] = 1LL * tagMul[p] * mul % mod;
}

void pushdownMul(int p)
{
    if (tagMul[p] != 1)
    {
        modifyMul(lson, tagMul[p]);
        modifyMul(rson, tagMul[p]);
        tagMul[p] = 1;
    }
}

void modifyAdd(int p, int add, int l, int r)
{
    pushdownMul(p);
    nodes[p] = (0LL + nodes[p] + 1LL * (r - l + 1) * add % mod) % mod;
    tagAdd[p] = (0LL + tagAdd[p] + add) % mod;
}

void pushdownAdd(int p, int l, int r)
{
    if (tagAdd[p] != 0)
    {
        modifyAdd(lson, tagMul[p], l, mid), modifyAdd(rson, tagMul[p], mid + 1, r);
        tagAdd[p] = 0;
    }
}

void pushdown(int p, int l, int r) { pushdownMul(p), pushdownAdd(p, l, r); }

void build(int l, int r, int p)
{
    tagMul[p] = 1;
    if (l == r)
        return;
    build(l, mid, lson), build(mid + 1, r, rson);
}

void pushup(int p) { nodes[p] = (0LL + nodes[lson] + nodes[rson]) % mod; }

void updateMul(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(modifyMul(p, val));
    pushdown(p, l, r);
    if (ql <= mid)
        updateMul(ql, qr, l, mid, lson, val);
    if (mid < qr)
        updateMul(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

void updateAdd(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(modifyAdd(p, val, l, r));
    pushdown(p, l, r);
    if (ql <= mid)
        updateAdd(ql, qr, l, mid, lson, val);
    if (mid < qr)
        updateAdd(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p, l, r);
    int ret = 0;
    if (ql <= mid)
        ret = (0LL + ret + query(ql, qr, l, mid, lson)) % mod;
    if (mid < qr)
        ret = (0LL + ret + query(ql, qr, mid + 1, r, rson)) % mod;
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &segs[i].first, &segs[i].second);
    for (int i = 1; i <= m; i++)
        scanf("%d", &xi[i]);
    sort(xi + 1, xi + 1 + m), m = unique(xi + 1, xi + 1 + m) - xi - 1;
    for (int i = 1; i <= n; i++)
    {
        segs[i].first = lower_bound(xi + 1, xi + 1 + m, segs[i].first) - xi;
        segs[i].second = upper_bound(xi + 1, xi + 1 + m, segs[i].second) - xi - 1;
    }
    sort(segs + 1, segs + 1 + n, [](const pii &lhs, const pii &rhs) { return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second); });
    build(0, m, 1), updateAdd(0, 0, 0, m, 1, 1);
    for (int i = 1; i <= n; i++)
        if (segs[i].first <= segs[i].second)
        {
            updateMul(segs[i].second, m, 0, m, 1, 2);
            updateAdd(segs[i].second, segs[i].second, 0, m, 1, query(segs[i].first - 1, segs[i].second - 1, 0, m, 1));
        }
    printf("%d\n", query(m, m, 0, m, 1));
    return 0;
} 