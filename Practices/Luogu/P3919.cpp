// P3919.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;

const int MAX_N = 1e6 + 2000;

int n, m, roots[MAX_N], ptot, source[MAX_N];

struct node
{
    int num, lson, rson;
} nodes[MAX_N * 30];

int build(int l, int r)
{
    int p = ++ptot;
    if (l == r)
    {
        nodes[p].num = source[l];
        return p;
    }
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
    {
        nodes[p].num = val;
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, val);
    return p;
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return nodes[p].num;
    if (qx <= mid)
        return query(qx, l, mid, nodes[p].lson);
    else
        return query(qx, mid + 1, r, nodes[p].rson);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &source[i]);
    roots[0] = build(1, n);
    for (int i = 1; i <= m; i++)
    {
        int ver, opt, a, b;
        scanf("%d%d%d", &ver, &opt, &a);
        if (opt == 1)
            scanf("%d", &b), roots[i] = update(a, 1, n, roots[ver], b);
        else
            roots[i] = roots[ver], printf("%d\n", query(a, 1, n, roots[ver]));
    }
    return 0;
}