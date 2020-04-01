// P4097.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200, mod = 39989;

int n, lastans, segtot;
double ki[MAX_N], bi[MAX_N];

struct node
{
    int id;
    bool tag;
    double k, b;
} nodes[MAX_N << 2];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

void update(int l, int r, int p, int id, double k, double b)
{
    if (nodes[p].tag == false)
        return (void)(nodes[p].tag = true, nodes[p].id = id, nodes[p].k = k, nodes[p].b = b);
    double cl = l * nodes[p].k + nodes[p].b, cr = r * nodes[p].k + nodes[p].b;
    double nl = l * k + b, nr = r * k + b;
    if (nl >= cl && nr >= cr)
        return (void)(nodes[p].id = id, nodes[p].k = k, nodes[p].b = b);
    if (cl >= nl && cr >= nr)
        return;
    double intersect = (nodes[p].b - b) / (k - nodes[p].k);
    if (intersect <= mid)
        if (cl > nl)
            update(l, mid, lson, nodes[p].id, nodes[p].k, nodes[p].b), nodes[p].id = id, nodes[p].k = k, nodes[p].b = b;
        else
            update(l, mid, lson, id, k, b);
    else if (cl > nl)
        update(mid + 1, r, rson, id, k, b);
    else
        update(mid + 1, r, rson, nodes[p].id, nodes[p].k, nodes[p].b), nodes[p].id = id, nodes[p].k = k, nodes[p].b = b;
}

void update(int ql, int qr, int l, int r, int p, int id, double k, double b)
{
    if (ql <= l && r <= qr)
        return (void)(update(l, r, p, id, k, b));
    if (ql <= mid)
        update(ql, qr, l, mid, lson, id, k, b);
    if (mid < qr)
        update(ql, qr, mid + 1, r, rson, id, k, b);
}

int gmax(int x, int y, double inp)
{
    double yx = ki[x] * inp + bi[x], yy = ki[y] * inp + bi[y];
    return yx < yy ? y : x;
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p].id;
    int ret = nodes[p].id;
    if (qx <= mid)
        ret = gmax(ret, query(qx, l, mid, lson), qx);
    else
        ret = gmax(ret, query(qx, mid + 1, r, rson), qx);
    return ret;
}

#undef mid
#undef rson
#undef lson

int main()
{
    scanf("%d", &n);
    while (n--)
    {
        int opt, xa, ya, xb, yb;
        scanf("%d%d", &opt, &xa);
        if (opt == 0)
            xa = (xa + lastans - 1) % mod + 1, printf("%d\n", lastans = query(xa, 1, MAX_N, 1));
        else
        {
            scanf("%d%d%d", &ya, &xb, &yb);
            xa = (xa + lastans - 1) % mod + 1, ya = (ya + lastans - 1) % int(1e9) + 1;
            xb = (xb + lastans - 1) % mod + 1, yb = (yb + lastans - 1) % int(1e9) + 1;
            if (xa > xb)
                swap(xa, xb), swap(ya, yb);
            if (xb == xa)
                ki[++segtot] = 0, bi[segtot] = max(ya, yb);
            else
                ki[++segtot] = double(yb - ya) / double(xb - xa), bi[segtot] = ya - ki[segtot] * xa;
            update(xa, xb, 1, MAX_N, 1, segtot, ki[segtot], bi[segtot]);
        }
    }
    return 0;
}