// P3224.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 4001000;

struct node
{
    int lson, rson, sum;
} nodes[MAX_N];
map<int, int> mp;

int ptot, n, m, q, impt[MAX_N], root[MAX_N], fa[MAX_N];
char opt[20];

int merge(int pa, int pb, int l, int r)
{
    if (pa == 0)
        return pb;
    if (pb == 0)
        return pa;
    nodes[pa].sum += nodes[pb].sum;
    if (l == r)
        return pa;
    int mid = (l + r) >> 1;
    nodes[pa].lson = merge(nodes[pa].lson, nodes[pb].lson, l, mid);
    nodes[pa].rson = merge(nodes[pa].rson, nodes[pb].rson, mid + 1, r);
    return pa;
}

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
    if (k > nodes[p].sum)
        return -1;
    if (l == r)
        return l;
    int lval = nodes[nodes[p].lson].sum, mid = (l + r) >> 1;
    if (k > lval)
        return query(k - lval, mid + 1, r, nodes[p].rson);
    else
        return query(k, l, mid, nodes[p].lson);
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main()
{
    mp[-1] = -1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &impt[i]), root[i] = update(impt[i], 1, n, root[i], 1), fa[i] = i, mp[impt[i]] = i;
    for (int i = 1, u, v; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        if (find(u) != find(v))
        {
            root[find(v)] = merge(root[find(v)], root[find(u)], 1, n);
            fa[find(u)] = find(v);
        }
    }
    scanf("%d", &q);
    while (q--)
    {
        int u, v;
        scanf("%s%d%d", opt + 1, &u, &v);
        if (opt[1] == 'B')
        {
            if (find(u) != find(v))
            {
                root[find(v)] = merge(root[find(v)], root[find(u)], 1, n);
                fa[find(u)] = find(v);
            }
        }
        else
        {
            int tmp = query(v, 1, n, root[find(u)]);
            printf("%d\n", mp[tmp]);
        }
    }
    return 0;
}