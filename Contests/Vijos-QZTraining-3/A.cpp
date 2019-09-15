// A.cpp
#include <bits/stdc++.h>
#define ll long long
#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson (lson | 1)

using namespace std;

const int MAX_N = 2e6 + 200;

ll tree[MAX_N << 2], tag[MAX_N << 2], prefix[MAX_N], n;

void pushdown(int p)
{
    if (tag[p] != 0)
    {
        tag[lson] += tag[p], tree[lson] += tag[p];
        tag[rson] += tag[p], tree[rson] += tag[p];
        tree[p] = min(tree[lson], tree[rson]);
        tag[p] = 0;
    }
}

void pushup(int p) { tree[p] = min(tree[lson], tree[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(tree[p] = prefix[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, ll val, int p)
{
    if (ql <= l && r <= qr)
        return (void)(tree[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, val, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, val, rson);
    pushup(p);
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    pushdown(p);
    ll ans = 1e18;
    if (ql <= mid)
        ans = min(ans, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ans = min(ans, query(ql, qr, mid + 1, r, rson));
    return ans;
}

int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &prefix[i]), prefix[i + n] = prefix[i];
    for (int i = 1; i <= 2 * n; i++)
        prefix[i] += prefix[i - 1];
    build(1, n << 1, 1);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        // edit the prefix;
        int mi_val = query(1 + i, n + i, 1, n << 1, 1);
        if (mi_val >= prefix[i])
            ans++;
    }
    printf("%d", ans);
    return 0;
}