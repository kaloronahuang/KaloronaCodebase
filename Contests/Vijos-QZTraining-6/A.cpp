// A.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100100;

int n, m, q, roots[MAX_N], ptot, rk[MAX_N], atrk[MAX_N], ufs[MAX_N], siz[MAX_N];
char opt[20];

struct node
{
    int sum, lson, rson;
} nodes[MAX_N * 100];

int find(int x) { return ufs[x] == x ? x : ufs[x] = find(ufs[x]); }

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    if (l == r)
    {
        nodes[p].sum += val;
        return p;
    }
    int mid = (l + r) >> 1;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
    return p;
}

int query(int k, int l, int r, int p)
{
    if (l == r && k != 1)
        return 0;
    if (l == r)
        return l;
    int mid = (l + r) >> 1;
    if (nodes[nodes[p].lson].sum < k)
        return query(k - nodes[nodes[p].lson].sum, mid + 1, r, nodes[p].rson);
    else
        return query(k, l, mid, nodes[p].lson);
}

int merge(int x, int y)
{
    if (x == 0 || y == 0)
        return max(x, y);
    nodes[x].sum += nodes[y].sum;
    nodes[x].lson = merge(nodes[x].lson, nodes[y].lson);
    nodes[x].rson = merge(nodes[x].rson, nodes[y].rson);
    return x;
}

void unite(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;
    if (siz[x] < siz[y])
        swap(x, y);
    ufs[y] = ufs[x], siz[x] += siz[y];
    roots[x] = merge(roots[x], roots[y]);
}

int main()
{
    scanf("%d%d", &n, &m);
    atrk[0] = -1;
    for (int i = 1; i <= n; i++)
        scanf("%d", &rk[i]), atrk[rk[i]] = i, roots[i] = update(rk[i], 1, n, 0, 1);
    for (int i = 1; i <= n; i++)
        ufs[i] = i, siz[i] = 1;
    for (int i = 1, u, v; i <= m; i++)
        scanf("%d%d", &u, &v), unite(u, v);
    scanf("%d", &q);
    while (q--)
    {
        int u, v;
        scanf("%s%d%d", opt + 1, &u, &v);
        if (opt[1] == 'B')
            unite(u, v);
        else
        {
            u = find(u);
            if (nodes[roots[u]].sum < v)
                puts("-1");
            else
                printf("%d\n", atrk[query(v, 1, n, roots[u])]);
        }
    }
    return 0;
}