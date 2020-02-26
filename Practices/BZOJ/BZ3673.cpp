// BZ3673.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 2e4 + 200, MAX_P = 4e5 + 200;

int n, m, ptot, roots[MAX_N], T;

struct node
{
    int lson, rson, val;
} nodes[MAX_P];

#define mid ((l + r) >> 1)

int build(int l, int r)
{
    int p = ++ptot;
    if (l == r)
        return (nodes[p].val = l, p);
    nodes[p].lson = build(l, mid);
    nodes[p].rson = build(mid + 1, r);
    return p;
}

int query(int qx, int l, int r, int p)
{
    if (l == r)
        return p;
    if (qx <= mid)
        return query(qx, l, mid, nodes[p].lson);
    else
        return query(qx, mid + 1, r, nodes[p].rson);
}

int find(int root, int x)
{
    int tmp = query(x, 1, n, root);
    if (x == nodes[tmp].val)
        return tmp;
    else
        return find(root, nodes[tmp].val);
}

int update(int qx, int l, int r, int val, int pre)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    if (l == r)
        return (nodes[p].val = val, p);
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, val, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, val, nodes[pre].rson);
    return p;
}

void merge(int x, int y) { roots[T] = update(nodes[x].val, 1, n, nodes[y].val, roots[T - 1]); }

int main()
{
    scanf("%d%d", &n, &m), roots[0] = build(1, n);
    for (int i = 1; i <= m; i++)
    {
        int opt, x, y;
        scanf("%d%d", &opt, &x);
        if (opt == 2)
            roots[i] = roots[x];
        else
        {
            T = i, roots[i] = roots[i - 1], scanf("%d", &y);
            if (opt == 1)
            {
                int fx = find(roots[T], x), fy = find(roots[T], y);
                if (nodes[fx].val != nodes[fy].val)
                    merge(fx, fy);
            }
            else
            {
                int fx = find(roots[T], x), fy = find(roots[T], y);
                int res = (nodes[fx].val == nodes[fy].val);
                printf("%d\n", res);
            }
        }
    }
    return 0;
}