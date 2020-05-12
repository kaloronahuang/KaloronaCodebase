// P4198.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

int n, m, tag[MAX_N << 2];
double nodes[MAX_N << 2], ai[MAX_N];

#define lson (p << 1)
#define rson ((p << 1) | 1)
#define mid ((l + r) >> 1)

int query(double qx, int l, int r, int p)
{
    if (nodes[p] <= qx)
        return 0;
    if (ai[l] > qx)
        return tag[p];
    if (l == r)
        return ai[l] > qx;
    if (nodes[lson] <= qx)
        return query(qx, mid + 1, r, rson);
    else
        return query(qx, l, mid, lson) + tag[p] - tag[lson];
}

void pushup(int p, int l, int r)
{
    nodes[p] = max(nodes[lson], nodes[rson]);
    tag[p] = tag[lson] + query(nodes[lson], mid + 1, r, rson);
}

void update(int qx, int l, int r, int p, int val)
{
    if (l == r)
    {
        nodes[p] = 1.0 * val / l, tag[p] = 1;
        return;
    }
    if (qx <= mid)
        update(qx, l, mid, lson, val);
    else
        update(qx, mid + 1, r, rson, val);
    pushup(p, l, r);
}

int main()
{
    scanf("%d%d", &n, &m);
    while (m--)
    {
        int x, y;
        scanf("%d%d", &x, &y), ai[x] = 1.0 * y / x;
        update(x, 1, n, 1, y), printf("%d\n", tag[1]);
    }
    return 0;
}