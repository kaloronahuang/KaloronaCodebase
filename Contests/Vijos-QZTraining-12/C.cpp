// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 800010, INF = 0x3f3f3f3f;

int min_val[MAX_N], seq[MAX_N], n, q, ans;
vector<int> queries[MAX_N];

#define mid ((l + r) >> 1)
#define lson (p << 1)
#define rson ((p << 1) | 1)

void pushup(int p)
{
    min_val[p] = min(min_val[lson], min_val[rson]);
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(min_val[p] = ((l == 0) ? 0 : INF));
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(min_val[p] = min(min_val[p], val));
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return min_val[p];
    int ret = INF;
    if (ql <= mid)
        ret = min(ret, query(ql, qr, l, mid, lson));
    if (mid < qr)
        ret = min(ret, query(ql, qr, mid + 1, r, rson));
    return ret;
}

#undef mid
#undef lson
#undef rson

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &seq[i]), ans += !seq[i];
    scanf("%d", &q);
    for (int i = 1, x, y; i <= q; i++)
        scanf("%d%d", &x, &y), queries[x - 1].push_back(y);
    build(0, n, 1);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0, siz = queries[i].size(); j < siz; j++)
            update(queries[i][j], 0, n, 1, query(i, queries[i][j], 0, n, 1));
        update(i + 1, 0, n, 1, query(i, i, 0, n, 1) + (seq[i] ? 1 : -1));
    }
    printf("%d\n", ans + query(n, n, 0, n, 1));
    return 0;
}