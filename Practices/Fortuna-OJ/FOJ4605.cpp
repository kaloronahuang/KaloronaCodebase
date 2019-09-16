// FOJ4605.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int seq[MAX_N], n, m, opt[MAX_N], li[MAX_N], ri[MAX_N], tmp[MAX_N];
int tree[MAX_N << 2], tag[MAX_N << 2], q;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    tree[p] = tree[lson] + tree[rson];
}

void pushdown(int l, int r, int p)
{
    if (tag[p] != -1)
    {
        tag[lson] = tag[p], tag[rson] = tag[p];
        tree[lson] = (mid - l + 1) * tag[p], tree[rson] = (r - mid) * tag[p];
        tag[p] = -1;
    }
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(tree[p] = tmp[l]);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
    {
        tree[p] = (r - l + 1) * val, tag[p] = val;
        return;
    }
    pushdown(l, r, p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return tree[p];
    pushdown(l, r, p);
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}

#undef lson
#undef rson
#undef mid

bool check(int mid)
{
    memset(tag, -1, sizeof(tag));
    for (int i = 1; i <= n; i++)
        tmp[i] = (seq[i] >= mid);
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        int op = opt[i], l = li[i], r = ri[i];
        int ones = query(l, r, 1, n, 1);
        update(l, r, 1, n, 1, 0);
        if (op == 0 && ones != 0)
            update(r - ones + 1, r, 1, n, 1, 1);
        else if (ones != 0)
            update(l, l + ones - 1, 1, n, 1, 1);
    }
    return (query(q, q, 1, n, 1) == 1);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &opt[i], &li[i], &ri[i]);
    scanf("%d", &q);
    int l = 1, r = n, ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            l = mid + 1, ans = mid;
        else
            r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}