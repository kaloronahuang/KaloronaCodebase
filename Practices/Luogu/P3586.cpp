// P3586.cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e6 + 200;

typedef long long ll;

int n, q, ptot, root, seq[MAX_N];
char cmdlet[10];

struct node
{
    int sum, lson, rson;
    ll valsum;
} nodes[MAX_N * 30];

#define mid ((l + r) >> 1)

int update(int qx, int l, int r, int p, int val)
{
    if (p == 0)
        p = ++ptot;
    nodes[p].sum += val, nodes[p].valsum += qx * val;
    if (l == r)
        return p;
    if (qx <= mid)
        nodes[p].lson = update(qx, l, mid, nodes[p].lson, val);
    else
        nodes[p].rson = update(qx, mid + 1, r, nodes[p].rson, val);
    return p;
}

ll querySum(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].valsum;
    ll ret = 0;
    if (ql <= mid)
        ret += querySum(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += querySum(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int querySiz(int ql, int qr, int l, int r, int p)
{
    if (p == 0)
        return 0;
    if (ql <= l && r <= qr)
        return nodes[p].sum;
    int ret = 0;
    if (ql <= mid)
        ret += querySiz(ql, qr, l, mid, nodes[p].lson);
    if (mid < qr)
        ret += querySiz(ql, qr, mid + 1, r, nodes[p].rson);
    return ret;
}

int main()
{
    scanf("%d%d", &n, &q), root = update(0, 0, 1e9, 0, n);
    while (q--)
    {
        int x, y;
        scanf("%s%d%d", cmdlet + 1, &x, &y);
        if (cmdlet[1] == 'U')
            update(seq[x], 0, 1e9, root, -1), seq[x] = y, update(seq[x], 0, 1e9, root, 1);
        else
        {
            int tot = querySiz(y, 1e9, 0, 1e9, root);
            ll sum = y ? querySum(0, y - 1, 0, 1e9, root) : 0;
            puts(sum >= 1LL * (x - tot) * y ? "TAK" : "NIE");
        }
    }
    return 0;
}