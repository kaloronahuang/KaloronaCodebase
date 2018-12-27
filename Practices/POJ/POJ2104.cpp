// POJ2104.cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define mid ((l + r) >> 1)
using namespace std;
const int MX_N = 1e5 + 20;
struct node
{
    int ls, rs, info, weight;
} nodes[(2 << 5) * MX_N];
int n, m, ncnt, seq[MX_N], misc[MX_N], len, roots[MX_N], sum[(2 << 5) * MX_N];
int getId(int val) { return lower_bound(misc + 1, misc + 1 + len, val) - misc; }
int build(int l, int r)
{
    int p = ++ncnt;
    if (l == r)
        return p;
    nodes[p].ls = build(l, mid);
    nodes[p].rs = build(mid + 1, r);
    return p;
}
int update(int l, int r, int previous, int c)
{
    int p = ++ncnt;
    nodes[p].ls = nodes[previous].ls;
    nodes[p].rs = nodes[previous].rs;
    sum[p] = sum[previous] + 1;
    if (l == r)
        return p;
    if (c <= mid)
        nodes[p].ls = update(l, mid, nodes[p].ls, c);
    else
        nodes[p].rs = update(mid + 1, r, nodes[p].rs, c);
    return p;
}
int query(int l, int r, int previous, int now, int k)
{
    int lsWeight = sum[nodes[now].ls] - sum[nodes[previous].ls];
    if (l == r)
        return l;
    if (k <= lsWeight)
        return query(l, mid, nodes[previous].ls, nodes[now].ls, k);
    else
        return query(mid + 1, r, nodes[previous].rs, nodes[now].rs, k - lsWeight);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &seq[i]);
    memcpy(misc, seq, sizeof(misc));
    sort(misc + 1, misc + 1 + n);
    len = unique(misc + 1, misc + 1 + n) - misc - 1;
    roots[0] = build(1, len);
    for (int i = 1; i <= n; i++)
        roots[i] = update(1, len, roots[i - 1], getId(seq[i]));
    while (m--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", misc[query(1, len, roots[l - 1], roots[r], k)]);
    }
    return 0;
}