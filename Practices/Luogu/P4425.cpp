// P4425.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e5 + 200, INF = 0x3f3f3f3f;

int n, m, typ, Ti[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p] > qx ? qx + l : INF;
    return nodes[rson] > qx ? min(tag[p], query(qx, mid + 1, r, rson)) : query(qx, l, mid, lson);
}

void pushup(int p, int l, int r)
{
    nodes[p] = max(nodes[lson], nodes[rson]);
    tag[p] = query(nodes[rson], l, mid, lson);
}

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = Ti[l] - l, tag[p] = INF);
    build(l, mid, lson), build(mid + 1, r, rson);
    pushup(p, l, r);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
        return (void)(nodes[p] = val - l);
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p, l, r);
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d%d", &n, &m, &typ);
    for (int i = 1; i <= n; i++)
        scanf("%d", &Ti[i]);
    int lastans;
    build(1, n, 1), printf("%d\n", lastans = query(nodes[1] - n, 1, n, 1) + n);
    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y), x ^= typ * lastans, y ^= typ * lastans;
        update(x, 1, n, 1, y);
        printf("%d\n", lastans = query(nodes[1] - n, 1, n, 1) + n);
    }
    return 0;
}