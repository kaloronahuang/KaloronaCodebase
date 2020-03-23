// SP11470.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e5 + 200;

typedef long long ll;

int n, q, ptot, time_frame, roots[MAX_N], ai[MAX_N];
char cmdlet[20];

struct node
{
    ll sum, tag;
    int lson, rson;
} nodes[MAX_N * 50];

#define mid ((l + r) >> 1)

int update(int ql, int qr, int l, int r, int pre, int val)
{
    int p = ++ptot;
    nodes[p] = nodes[pre];
    nodes[p].sum += 1LL * val * (min(qr, r) - max(ql, l) + 1);
    if (ql <= l && r <= qr)
        return nodes[p].tag += val, p;
    if (ql <= mid)
        nodes[p].lson = update(ql, qr, l, mid, nodes[pre].lson, val);
    if (mid < qr)
        nodes[p].rson = update(ql, qr, mid + 1, r, nodes[pre].rson, val);
    return p;
}

ll query(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    ll ret = 1LL * (min(qr, r) - max(ql, l) + 1) * nodes[p].tag;
    if (ql <= mid)
        ret += query(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += query(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int build(int l, int r)
{
    int p = ++ptot;
    if (l == r)
        return nodes[p].sum = ai[l], p;
    nodes[p].lson = build(l, mid);
    nodes[p].rson = build(mid + 1, r);
    nodes[p].sum = nodes[nodes[p].lson].sum + nodes[nodes[p].rson].sum;
    return p;
}

#undef mid

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &ai[i]);
    roots[0] = build(1, n);
    while (q--)
    {
        int l, r, d;
        scanf("%s", cmdlet + 1);
        if (cmdlet[1] == 'C')
        {
            scanf("%d%d%d", &l, &r, &d), time_frame++;
            roots[time_frame] = update(l, r, 1, n, roots[time_frame - 1], d);
        }
        else if (cmdlet[1] == 'Q')
            scanf("%d%d", &l, &r), printf("%lld\n", query(l, r, 1, n, roots[time_frame]));
        else if (cmdlet[1] == 'H')
            scanf("%d%d%d", &l, &r, &d), printf("%lld\n", query(l, r, 1, n, roots[d]));
        else
            scanf("%d", &d), time_frame = d;
    }
    return 0;
}