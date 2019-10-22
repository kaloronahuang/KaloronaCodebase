// P3834.cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)

using namespace std;

const int MX_N = 2 * 1e5 + 2000;

struct node
{
    int ls, rs, f;
} nodes[(2 << 5) * MX_N];

int n, m, seq[MX_N], vec[MX_N], len, ncnt, roots[MX_N];

int getId(int x) { return lower_bound(vec + 1, vec + 1 + len, x) - vec; }

int build(int l, int r)
{
    int p = ++ncnt;
    if (l == r)
        return p;
    nodes[p].ls = build(l, mid);
    nodes[p].rs = build(mid + 1, r);
    return p;
}

int update(int l, int r, int c, int previous)
{
    int p = ++ncnt;
    nodes[p].f = nodes[previous].f + 1;
    nodes[p].ls = nodes[previous].ls;
    nodes[p].rs = nodes[previous].rs;
    if (l == r)
        return p;
    if (c <= mid)
        nodes[p].ls = update(l, mid, c, nodes[previous].ls);
    else
        nodes[p].rs = update(mid + 1, r, c, nodes[previous].rs);
    return p;
}

int query(int l, int r, int k, int previous, int now)
{
    if (l == r)
        return l;
    int lsWeight = nodes[nodes[now].ls].f - nodes[nodes[previous].ls].f;
    if (k <= lsWeight)
        return query(l, mid, k, nodes[previous].ls, nodes[now].ls);
    else
        return query(mid + 1, r, k - lsWeight, nodes[previous].rs, nodes[now].rs);
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    memcpy(vec, seq, sizeof(vec));
    sort(vec + 1, vec + 1 + n);
    len = unique(vec + 1, vec + 1 + n) - vec - 1;
    roots[0] = build(1, len);
    for (int i = 1; i <= n; i++)
        roots[i] = update(1, len, getId(seq[i]), roots[i - 1]);
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", vec[query(1, len, k, roots[l - 1], roots[r])]);
    }
    return 0;
}