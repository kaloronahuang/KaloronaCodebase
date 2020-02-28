// CF1179C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200, RANGE = 1e6, INF = 0x7fffffff, inf = 0x3f3f3f3f;

int n, m, ai[MAX_N], bi[MAX_N], q, nodes[MAX_N << 2], tag[MAX_N << 2], bucket[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p)
{
    if (tag[p])
    {
        nodes[lson] += tag[p], nodes[rson] += tag[p];
        tag[lson] += tag[p], tag[rson] += tag[p];
        tag[p] = 0;
    }
}

void pushup(int p) { nodes[p] = min(nodes[lson], nodes[rson]); }

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = inf);
    build(l, mid, lson), build(mid + 1, r, rson);
    return;
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] += val, tag[p] += val);
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int l, int r, int p)
{
    if (nodes[p] >= 0)
        return -1;
    if (l == r)
        return l;
    pushdown(p);
    if (nodes[rson] < 0)
        return query(mid + 1, r, rson);
    else
        return query(l, mid, lson);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &m), build(1, RANGE, 1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]), bucket[ai[i]]++;
        if (bucket[ai[i]] == 1)
            update(ai[i], ai[i], 1, RANGE, 1, -inf);
        update(1, ai[i], 1, RANGE, 1, -1);
    }
    for (int i = 1; i <= m; i++)
        scanf("%d", &bi[i]), update(1, bi[i], 1, RANGE, 1, 1);
    scanf("%d", &q);
    while (q--)
    {
        int opt, pos, x;
        scanf("%d%d%d", &opt, &pos, &x);
        if (opt == 1)
        {
            update(1, ai[pos], 1, RANGE, 1, 1), bucket[ai[pos]]--;
            if (bucket[ai[pos]] == 0)
                update(ai[pos], ai[pos], 1, RANGE, 1, inf);
            ai[pos] = x, update(1, ai[pos], 1, RANGE, 1, -1), bucket[ai[pos]]++;
            if (bucket[ai[pos]] == 1)
                update(ai[pos], ai[pos], 1, RANGE, 1, -inf);
        }
        else
            update(1, bi[pos], 1, RANGE, 1, -1), bi[pos] = x, update(1, bi[pos], 1, RANGE, 1, 1);
        printf("%d\n", query(1, RANGE, 1));
    }
    return 0;
}