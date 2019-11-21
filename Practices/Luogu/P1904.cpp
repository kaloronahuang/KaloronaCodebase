// P1904.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 10100;

int seq[MAX_N], nodes[MAX_N << 2], tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushup(int p)
{
    nodes[p] = max(nodes[lson], nodes[rson]);
}

void pushdown(int p)
{
    if (tag[p])
    {
        nodes[lson] = max(nodes[lson], tag[p]), nodes[rson] = max(nodes[rson], tag[p]);
        tag[lson] = max(tag[p], tag[lson]), tag[rson] = max(tag[p], tag[rson]);
        tag[p] = 0;
    }
}

void update(int ql, int qr, int l, int r, int p, int val)
{
    if (ql <= l && r <= qr)
        return (void)(nodes[p] = max(nodes[p], val), tag[p] = max(tag[p], val));
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
    pushup(p);
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p];
    pushdown(p);
    if (qx <= mid)
        return query(qx, l, mid, lson);
    else
        return query(qx, mid + 1, r, rson);
}

#undef mid
#undef rson
#undef lson

int main()
{
    int l, r, h;
    while (scanf("%d%d%d", &l, &h, &r) != EOF)
        update(l, r - 1, 1, 10000, 1, h);
    for (int i = 1; i <= 10000; i++)
        seq[i] = query(i, 1, 10000, 1);
    for (int i = 1; i <= 10000; i++)
        if (seq[i] != seq[i - 1])
            printf("%d %d ", i, seq[i]);
    return 0;
}