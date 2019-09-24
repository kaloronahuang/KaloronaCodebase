// B.cpp
#include <bits/stdc++.h>
#define ld long double

using namespace std;

const int MAX_N = 1e5 + 200;

struct vec
{
    int x, y;
    vec operator+(const vec &v) const { return vec{x + v.x, y + v.x}; }
    bool operator==(const vec &v) const { return (x == v.x) && (y == v.y); }
} nodes[MAX_N << 2], tag[MAX_N << 2];

int n, q;

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void build(int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p] = vec{0, l});
    build(l, mid, lson), build(mid + 1, r, rson);
}

void pushdown(int p)
{
    if (tag[p] == vec{0, 0})
        return;
    nodes[lson] = nodes[lson] + tag[p], nodes[rson] = nodes[rson] + tag[p];
    tag[lson] = tag[lson] + tag[p], tag[rson] = tag[rson] + tag[p];
    tag[p] = vec{0, 0};
}

void update(int ql, int qr, int l, int r, int p, vec val)
{
    if (ql <= l && r <= qr)
    {
        nodes[p] = nodes[p] + val, tag[p] = tag[p] + val;
        return;
    }
    pushdown(p);
    if (ql <= mid)
        update(ql, qr, l, mid, lson, val);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, val);
}

vec query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p];
    pushdown(p);
    if (qx <= mid)
        return query(qx, l, mid, lson);
    else
        return query(qx, mid + 1, r, rson);
}

#undef lson
#undef rson
#undef mid

int main()
{
    scanf("%d%d", &n, &q);
    build(1, n, 1);
    while (q--)
    {
        int opt, a, b, dx, dy;
        scanf("%d%d", &opt, &a);
        if (opt == 0)
        {
            vec res = query(a, 1, n, 1);
            printf("%.1lf %.1lf\n", double(res.x), double(res.y));
        }
        else
        {
            scanf("%d%d%d", &b, &dx, &dy);
            update(a, b, 1, n, 1, vec{dx, dy});
        }
    }
    return 0;
}