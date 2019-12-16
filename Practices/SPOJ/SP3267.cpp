// SP3267.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 30100;

int n, ai[MAX_N], q, roots[MAX_N], ptot, pre[MAX_N * 200], last[MAX_N];
vector<int> vec;

struct node
{
    int cnt, lson, rson;
} nodes[MAX_N * 200];

int build(int l, int r)
{
    if (l == r)
        return ++ptot;
    int p = ++ptot, mid = (l + r) >> 1;
    nodes[p].lson = build(l, mid), nodes[p].rson = build(mid + 1, r);
    return p;
}

int update(int qx, int l, int r, int pre)
{
    int p = ++ptot;
    nodes[p].cnt = nodes[pre].cnt + 1;
    int mid = (l + r) >> 1;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[pre].lson);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[pre].rson);
    return p;
}

int query(int ql, int qr, int l, int r, int p, int pre)
{
    if (ql <= l && r <= qr)
        return nodes[p].cnt - nodes[pre].cnt;
    int ret = 0, mid = (l + r) >> 1;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson, nodes[pre].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson, nodes[pre].rson);
    return ret;
}

int main()
{
    scanf("%d", &n), roots[0] = build(1, n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &ai[i]);
        last[i] = pre[ai[i]] + 1, pre[ai[i]] = i;
        roots[i] = update(last[i], 1, n, roots[i - 1]);
    }
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(1, l, 1, n, roots[r], roots[l - 1]));
    }
    return 0;
}