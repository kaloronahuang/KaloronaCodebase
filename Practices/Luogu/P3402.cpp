// P3402.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
using namespace std;

const int MAX_N = 1e5 + 2000;

int n, m;

struct node
{
    int dep, fa, lson, rson;
} nodes[MAX_N * 40];
int roots[MAX_N << 1], ptot;

int build(int l, int r)
{
    int p = ++ptot;
    if (l == r)
    {
        nodes[p].fa = l;
        return p;
    }
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int l, int r, int pre, int target)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
    {
        nodes[p].fa = target, nodes[p].dep = nodes[pre].dep;
        return p;
    }
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson, target);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson, target);
    return p;
}

void adddep(int qx, int l, int r, int p)
{
    if (l == r)
        return (void)(nodes[p].dep++);
    if (qx <= mid)
        adddep(qx, l, mid, nodes[p].lson);
    else
        adddep(qx, mid + 1, r, nodes[p].rson);
}

int query_fa(int qx, int l, int r, int p)
{
    if (l == r)
        return p;
    if (qx <= mid)
        return query_fa(qx, l, mid, nodes[p].lson);
    else
        return query_fa(qx, mid + 1, r, nodes[p].rson);
}

int find(int x, int p)
{
    int y = query_fa(x, 1, n, p);
    if (nodes[y].fa == x)
        return y;
    else
        return find(nodes[y].fa, p);
}

int main()
{
    scanf("%d%d", &n, &m);
    roots[0] = build(1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt, a, b;
        scanf("%d%d", &opt, &a), roots[i] = roots[i - 1];
        if (opt == 1)
        {
            scanf("%d", &b);
            int fA = find(a, roots[i]), fB = find(b, roots[i]);
            if (fA == fB)
                continue;
            if (nodes[fA].dep > nodes[fB].dep)
                swap(fA, fB);
            roots[i] = update(nodes[fA].fa, 1, n, roots[i], nodes[fB].fa);
            if (nodes[fA].dep == nodes[fB].dep)
                adddep(nodes[fB].fa, 1, n, roots[i]);
        }
        else if (opt == 2)
            roots[i] = roots[a];
        else
        {
            scanf("%d", &b);
            int fA = find(a, roots[i]), fB = find(b, roots[i]);
            puts((fA == fB) ? "1" : "0");
        }
    }
    return 0;
}