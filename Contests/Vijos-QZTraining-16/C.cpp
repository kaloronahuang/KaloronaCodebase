// C.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int nodes[MAX_N << 2], n, m, opt, tmpx, tmpy;
bool tag[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void pushdown(int p, int l, int r)
{
    if (tag[p])
    {
        tag[lson] ^= 1, tag[rson] ^= 1;
        nodes[lson] = (mid - l + 1) - nodes[lson];
        nodes[rson] = (r - mid) - nodes[rson];
        tag[p] = 0;
    }
}

void pushup(int p) { return (void)(nodes[p] = nodes[lson] + nodes[rson]); }

void update(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] = (r - l + 1) - nodes[p], tag[p] ^= 1;
        return;
    }
    pushdown(p, l, r);
    if (ql <= mid)
        update(ql, qr, l, mid, lson);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson);
    pushup(p);
}

int query(int ql, int qr, int l, int r, int p)
{
    if (ql <= l && r <= qr)
        return nodes[p];
    pushdown(p, l, r);
    int ans = 0;
    if (ql <= mid)
        ans += query(ql, qr, l, mid, lson);
    if (mid < qr)
        ans += query(ql, qr, mid + 1, r, rson);
    return ans;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        scanf("%d%d%d", &opt, &tmpx, &tmpy);
        if (opt == 0)
            update(tmpx, tmpy, 1, n, 1);
        else
            printf("%d\n", query(tmpx, tmpy, 1, n, 1));
    }
    return 0;
}