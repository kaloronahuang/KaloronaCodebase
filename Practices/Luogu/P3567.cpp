// P3567.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 500100;

struct node
{
    int val, lson, rson;
} nodes[MAX_N * 20];

int n, m, ptot, roots[MAX_N], tmpl, tmpr;

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre], nodes[p].val++;
    if (l == r)
        return p;
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int qx, int l, int r, int lft, int rig)
{
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if ((2 * (nodes[nodes[rig].lson].val - nodes[nodes[lft].lson].val)) > qx)
        return query(qx, l, mid, nodes[lft].lson, nodes[rig].lson);
    if ((2 * (nodes[nodes[rig].rson].val - nodes[nodes[lft].rson].val)) > qx)
        return query(qx, mid + 1, r, nodes[lft].rson, nodes[rig].rson);
    return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, tmp; i <= n; i++)
        scanf("%d", &tmp), roots[i] = update(tmp, 1, n, roots[i - 1]);
    while (m--)
        scanf("%d%d", &tmpl, &tmpr), printf("%d\n", query(tmpr - tmpl + 1, 1, n, roots[tmpl - 1], roots[tmpr]));
    return 0;
}