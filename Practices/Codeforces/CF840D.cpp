// CF840D.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3e5 + 200;

int n, m, roots[MAX_N], ptot, ai[MAX_N];

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].sum++;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int l, int r, int p, int pre, int threshold)
{
    if (l == r)
        return l;
    if (nodes[p].sum - nodes[pre].sum <= threshold)
        return -1;
    if (nodes[nodes[p].lson].sum - nodes[nodes[pre].lson].sum > threshold)
    {
        int res = query(l, mid, nodes[p].lson, nodes[pre].lson, threshold);
        if (res > 0)
            return res;
    }
    if (nodes[nodes[p].rson].sum - nodes[nodes[pre].rson].sum > threshold)
        return query(mid + 1, r, nodes[p].rson, nodes[pre].rson, threshold);
    return -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]), roots[i] = update(ai[i], 1, n, roots[i - 1]);
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", query(1, n, roots[r], roots[l - 1], (r - l + 1) / k));
    }
    return 0;
}